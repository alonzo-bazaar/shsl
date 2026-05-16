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
           (rec 1 0))
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
	  ;; we use '|quote| instead of 'quote for consistency with how other
	  ;; alphanumeric symbols in the parsed result look
      ((eq l '\')
       (multiple-value-bind (quoted rst) (parse-off rst)
         (values (list '|quote| quoted) rst)))
      ((eq l '\`)
       (multiple-value-bind (quoted rst) (parse-off rst)
         (values (list '|quasiquote| quoted) rst)))
      ((eq l '\,)
       (multiple-value-bind (quoted rst) (parse-off rst)
         (values (list '|comma| quoted) rst)))

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
           (and (equal form '(|quote| (+ 1 2))) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off "`(+ 1 2)")
           (and (equal form '(|quasiquote| (+ 1 2))) (equal rst "")))

         (multiple-value-bind (form rst) (parse-off ",(+ 1 2)")
           (and (equal form '(|comma| (+ 1 2))) (equal rst "")))
         ))

(defclass shsl-frame ()
  ((bindings
	:type hash-table
	:initarg :bindings
	:accessor shsl-frame-bindings
	:initform (make-hash-table))))

(defclass shsl-env ()
  ((first
	:type shsl-frame
	:initarg :first
	:accessor shsl-env-first
	:initform (make-instance 'shsl-frame))
   (parent
	:type (or shsl-env null)
	:initarg :parent
	:accessor shsl-env-parent
	:initform nil)))

(defmethod lookup ((name symbol) (frame shsl-frame))
	(gethash name (shsl-frame-bindings frame)))

(defmethod lookup ((name symbol) (env shsl-env))
  (multiple-value-bind (val found) (lookup name (shsl-env-first env))
	(cond (found (values val t))
		  ((shsl-env-parent env) (lookup name (shsl-env-parent env)))
		  (t (values nil nil)))))

(defparameter *empty-env* (make-instance 'shsl-env))

(defclass shsl-fun ()
  ((env
	:type shsl-env
	:accessor shsl-fun-env
	:initarg :env)))
(defclass shsl-macro (shsl-fun) ())

(defclass shsl-builtin-fun (shsl-fun)
  ((env
	:initform *empty-env*)
   (inner
	:type (function (list) t)
	:accessor shsl-builtin-fun-inner
	:initarg :inner)))

(defclass shsl-builtin-macro (shsl-builtin-fun shsl-macro)
  ((inner
	:type (function (list) t)
	:accessor shsl-builtin-macro-inner
	:initarg :inner)))

(defparameter *initial-env-frame*
  (let ((tb (make-hash-table)))
	(macrolet ((builtin-fun-that (&body body)
				 `(make-instance 'shsl-builtin-fun
								 :inner (lambda (args) ,@body)))
			   (builtin-macro-that (&body body)
				 `(make-instance 'shsl-builtin-macro
								 :inner (lambda (args) ,@body))))

	  ;; no sanitization atm
	  (setf (gethash '|+| tb) (builtin-fun-that
							   (reduce #'+ args :initial-value 0)))
	  (setf (gethash '|-| tb) (builtin-fun-that
							   (- (car args)
								  (reduce #'+ (cdr args) :initial-value 0))))
	  (setf (gethash '|car| tb) (builtin-fun-that
								 (caar args)))
	  (setf (gethash '|cdr| tb) (builtin-fun-that
								 (cdar args)))

	  ;; no sanitization atm

	  (make-instance 'shsl-frame :bindings tb))))

(defparameter *initial-env* (make-instance 'shsl-env
										   :first *initial-env-frame*
										   :parent nil))

(defmethod shsl-apply ((fn shsl-builtin-fun) (args list))
  (funcall (shsl-builtin-fun-inner fn) args))

(defmethod shsl-macroexpand-1 ((mc shsl-builtin-macro) (args list))
  (funcall (shsl-builtin-macro-inner mc) args))

(defun shsl-fun-p (f) (typep f 'shsl-fun))
(defun shsl-macro-p (f) (typep f 'shsl-macro))

;; (defmethod shsl-macroexpand ((mc shsl-builtin-macro) (args list))
;;   (let ((me1 (shsl-macroexpand-1 args)))
;; 	(

(defun shsl-eval (expr env)
  (if (not (consp expr))
	  ;; eval atom
	  (cond
		((or (integerp expr) (stringp expr) (null expr))     ; self evaluating
		 expr) 
		((symbolp expr)                                      ; symbol lookup
		 (multiple-value-bind (val found) (lookup expr env)
		   (if found
			   val
			   (error "cannot find value of unbound symbol ~A~%" expr))))
		(t (error "unrecognized atomic expression ~A~%" expr)))

	  ;; eval compound
	  (cond
		;; special forms (quote if let lambda while begin et al.)
		((eq (car expr) '|quote|)
		 (unless (= (length expr) 2)
		   (error "malformed quote expression ~A, incorrect length ~A !"
				  expr (length expr)))
		 (cadr expr))

		((eq (car expr) '|if|)
		 (unless (or (= (length expr) 3) (= (length expr) 4))
		   (error "malformed if expression ~A, incorrect length ~A !"
				  expr (length expr)))
		 (if (shsl-eval (cadr expr) env)
			 (shsl-eval (caddr expr) env)
			 (shsl-eval (cadddr expr) env)))

		;; macros and procedures
		;; which can be either user defined or builtin
		(t
		 (let ((operator (shsl-eval (car expr) env))
			   (operands (cdr expr)))
		   (cond ((shsl-fun-p operator)
				  (shsl-apply
				   operator
				   (mapcar (lambda (x) (shsl-eval x env)) operands)))
				 ((shsl-macro-p operator)
				  (shsl-eval
				   (shsl-macroexpand-1 operator operands)
				   env))
				 (t (error "unrecognized operator ~A of expression ~A~%operator is neither a function or a macro~%" operator expr))))))))

(defmacro with-shsl-eval-str ((valsym str) &body body)
  `(multiple-value-bind (,valsym _) (parse-off ,str)
	 (declare (ignore _))
	 (let ((,valsym (shsl-eval ,valsym *initial-env*)))
	   ,@body)))

(assert (and
		 (with-shsl-eval-str (val "'a")
		   (equal val '|a|))
		 (with-shsl-eval-str (val "(+ 1 2)")
		   (equal val 3))
		 ))


#|
;; for later, I think it'd be a good idea to have a clos adjacent thing
(defclass if-expr (expr)
  ((clause :type expr :accessor :clause :initarg :clause)
   (then-part :type expr :accessor :then-part :initarg :then-part)
   (else-part :type expr :accessor :else-part :initarg :else-part)))

(defclass let-expr (expr)
  ((clause :type expr :accessor :clause :initarg :clause)
   (then-part :type expr :accessor :then-part :initarg :then-part)
   (else-part :type expr :accessor :else-part :initarg :else-part)))
|#
