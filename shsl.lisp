;; prototype file for how I'll implement shsl 
;; implement small parser and interpreter for subset of scheme
;; then use this prototype as basis for how to do it in c or c++
;; an embeddable lisp in lisp is not of much use when you already have lisp

;; get one lexeme (token) off of the string
;; return that lexeme plus the rest of the string
(defun lex-off (s)
  (cond
	;; are we done?
	((= 0 (length s)) nil)
	;; (if this check fails we can safely query for (char s 0))

	;; ignore whitespace
	;; TODO: for efficiency we might wanna dismiss multiple whitespaces in bulk
	((sb-unicode:whitespace-p (char s 0)) (lex-off (subseq s 1)))

	;; TODO: handle (ignore) comments

	;; brackets
	((char= (char s 0) #\() (values '\( (subseq s 1)))
	((char= (char s 0) #\)) (values '\) (subseq s 1)))
	((char= (char s 0) #\[) (values '\[ (subseq s 1)))
	((char= (char s 0) #\]) (values '\] (subseq s 1)))
	((char= (char s 0) #\{) (values '\{ (subseq s 1)))
	((char= (char s 0) #\}) (values '\} (subseq s 1)))

	;; other special shit
	((char= (char s 0) #\') (values '\' (subseq s 1)))
	((char= (char s 0) #\`) (values '\` (subseq s 1)))
	((char= (char s 0) #\,) (values '\, (subseq s 1)))

    ;; string literals
    ;; TODO: handle escapes and shit
    ;; as of now we shall just reach the next #\" and call it a day
	((char= (char s 0) #\")
     (let ((p (position #\" s :start 1)))
       (if (not p)
           (error "unterminated string literal!")
           (values (subseq s 1 p)
                   (subseq s (1+ p))))))

    ;; if it's not a special symbol or string literal
    ;; we shall handle symbols and numbers together:
    ;; have a general case "pick all the non special shit from here to the end"
    ;; and
    ;; - if it's number like, return a number
    ;; - if it's symbol like, return a symbol
    ;; it's simpler to handle the distinction between like
    ;; --internal, -123, 123, 123e10
    ;; if we're not having to peek and guess all the time
	((symbol-char-p (char s 0))
	 (let ((p (position-if-not #'symbol-char-p s)))
	   (values (or (string-to-number (subseq s 0 p))
                   (intern (subseq s 0 p)))
			   (if p (subseq s p) "")))) ; p could be nil if we reach end of str
										 ; in which case the rest/suffix after
										 ; our token is... well, nothing
										 ; empty string

	;; symbols (todo: add - as a symbol char)
	((alpha-char-p (char s 0))
	 (let ((p (position-if-not #'alpha-char-p s)))
	   (values (intern (subseq s 0 p))
			   (if p (subseq s p) ""))))

	(t (error "unrecognized token starter: ~a~%" (char s 0)))))

;; special characters are shit that once encountered means
;; "ight, stop, this is its own thing, you're done with your current token"
(defun special-char-p (c)
  (member c '(#\( #\) #\[ #\] #\{ #\} #\' #\` #\, #\") :test #'char=))

;; is this a character you could find in a symbol? (or number)
(defun symbol-char-p (c)
  (and (not (sb-unicode:whitespace-p c))
       (not (special-char-p c))))

;; convert string representation of a number to that number
;; in accordance with parse-don't-validate style, it returns a number if
;; the string is a number, and returns nil otherwise
;; TODO: floats and scientific notation
(defun string-to-number (s)
  (labels ((char-digit (c)
			 (- (char-code c) (char-code #\0))) ;; not too portable
		   (rec (i acc)
			 (cond ((>= i (length s)) acc)
				   ((digit-char-p (char s i))
					(rec (1+ i) (+ (* acc 10) (char-digit (char s i)))))
				   (t nil))))

	(cond ((= (length s) 0)
           (error "cannot read empty string as value!"))

          ;; does the number have a sign?
          ((member s '("+" "-") :test #'string=)
           nil)
          ((char= (char s 0) #\+)
           ((rec 1 0)))
          ((char= (char s 0) #\-)
           (let ((a (rec 1 0))) (and a (- a))))

          ;; default case
          (t
           (rec 0 0)))))

;; string-to-number tests (to be moved to some fiveam shit later)
(assert (and
		 (= (string-to-number "123") 123)
		 (= (string-to-number "23") 23)
		 (= (string-to-number "3") 3)
         (= (string-to-number "-123") -123)
         (equal (string-to-number "hello") nil)
         (equal (string-to-number "--internal") nil)
         (equal (string-to-number "-") nil)
        ))

;; lex-off tests  
(assert (and
		 (multiple-value-bind (tok rst) (lex-off "(hello)")
		   (and (equal tok '\() (equal rst "hello)")))

		 (multiple-value-bind (tok rst) (lex-off "hello)")
		   (and (equal tok '|hello|) (equal rst ")")))

		 (multiple-value-bind (tok rst) (lex-off ")")
		   (and (equal tok '\)) (equal rst "")))

		 (multiple-value-bind (tok rst) (lex-off "\"\"")
		   (and (equal tok "")) (equal rst ""))

		 (multiple-value-bind (tok rst) (lex-off "\"hello bitch\"")
		   (and (equal tok "hello bitch")) (equal rst ""))

		 (multiple-value-bind (tok rst) (lex-off "\"hello bitch\" how are you?")
		   (and (equal tok "hello bitch")) (equal rst " how are you?"))
         ))

;; parse first form off a string and return that form
;; plus the rest of the string
(defun parse-off (s)
  (multiple-value-bind (l rst) (lex-off s)
	(cond
	  ;; handle brackets
	  ((eq l '\() (parse-until rst :stop '\) :error-on '(\] \})))
	  ((eq l '\[) (parse-until rst :stop '\] :error-on '(\) \})))
	  ((eq l '\{) (parse-until rst :stop '\} :error-on '(\) \])))

	  ;; quote, quasiquote, comma
      ((eq l '\')
       (multiple-value-bind (quoted rst) (parse-off rst)
         (values (list 'quote quoted) rst)))
      ((eq l '\`)
       (multiple-value-bind (quoted rst) (parse-off rst)
         (values (list 'quasiquote quoted) rst)))
      ((eq l '\,)
       (multiple-value-bind (quoted rst) (parse-off rst)
         (values (list 'comma quoted) rst)))

	  ;; atoms (other special shit, or literals)
	  ((or (numberp l)
		   (stringp l)
		   (symbolp l))
	   (values l rst))

	  (t (error "unrecognized token [~a]~%" l)))))

;; parse forms off a string until you meet a given terminator
;; return a list of all stirngs you parsed off
;; plus the rest of the string (after the terminator)
(defun parse-until (s &key stop error-on)
  (labels ((rec (remainder-string acc)
			 (multiple-value-bind
				   (lex after-lex) (lex-off remainder-string)
			   (cond ((eq lex stop) (values (nreverse acc) after-lex))
					 ((null lex) (error "premature end of input stream"))
					 ((member lex error-on)
					  (error "mismatched list terminator: ~a~%" lex))
					 (t
					  (multiple-value-bind
							(expr after-expr) (parse-off remainder-string) 
						(rec after-expr (cons expr acc))))))))
	(rec s (list))))

;; (trace parse-off parse-until)
;; parse tests
(assert (and
         (multiple-value-bind (form rst) (parse-off "(hello)")
           (and (equal form '(|hello|)) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off "([hello])")
           (and (equal form '((|hello|))) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off "([hello] bois)")
           (and (equal form '((|hello|) |bois|)) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off "([{hello}] bois)")
           (and (equal form '(((|hello|)) |bois|)) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off "(+ 1 2)")
           (and (equal form '(+ 1 2)) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off "'(+ 1 2)")
           (and (equal form '(quote (+ 1 2))) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off "`(+ 1 2)")
           (and (equal form '(quasiquote (+ 1 2))) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off ",(+ 1 2)")
           (and (equal form '(comma (+ 1 2))) (equal rst "")))
         ))

;; evaluator
;; as of now, brutale brutale, the sicp tree walk

;; I want the following lispy shit
;; if let do lambda defvar defun defmacro set setq progn
;; TODO: lambda lists?

;; and the following scripty shit
;; while until

;; plus the following builtin funs
;; + - * /
;; and builtin macros
;; and or (short circuiting: ergo macro)

(defclass if-expr (expr)
  ((clause :type expr :accessor :clause :initarg :clause)
   (then-part :type expr :accessor :then-part :initarg :then-part)
   (else-part :type expr :accessor :else-part :initarg :else-part)))

(defclass let-expr (expr)
  ((clause :type expr :accessor :clause :initarg :clause)
   (then-part :type expr :accessor :then-part :initarg :then-part)
   (else-part :type expr :accessor :else-part :initarg :else-part)))
