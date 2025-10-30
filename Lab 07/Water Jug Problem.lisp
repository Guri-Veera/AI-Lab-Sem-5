(defun state->key (state)
  "Return a string key for STATE (a list of integers) for hashing/visited checks."
  (princ-to-string state))

(defun goal-reached-p (state target)
  "Return true if any jug in STATE equals TARGET."
  (member target state :test #'=))

(defun fill-action (state caps i)
  "Return new state after filling jug i (0-based index)."
  (let ((new (copy-list state)))
    (setf (nth i new) (nth i caps))
    new))

(defun empty-action (state i)
  "Return new state after emptying jug i."
  (let ((new (copy-list state)))
    (setf (nth i new) 0)
    new))

(defun pour-action (state caps i j)
  "Return new state after pouring from jug i to jug j."
  (let* ((new (copy-list state))
         (amount-in (nth i new))
         (space (- (nth j caps) (nth j new)))
         (transfer (min amount-in space)))
    (when (> transfer 0)
      (setf (nth i new) (- (nth i new) transfer))
      (setf (nth j new) (+ (nth j new) transfer)))
    new))

(defun neighbors-with-actions (state caps)
  "Generate (new-state action-desc) pairs for all legal moves from STATE."
  (let ((n (length state))
        (result nil))
    ;; fill moves
    (dotimes (i n)
      (let ((s (fill-action state caps i)))
        (unless (equal s state)
          (push (cons s (format nil "Fill ~A" i)) result))))
    ;; empty moves
    (dotimes (i n)
      (let ((s (empty-action state i)))
        (unless (equal s state)
          (push (cons s (format nil "Empty ~A" i)) result))))
    ;; pour moves i -> j
    (dotimes (i n)
      (dotimes (j n)
        (unless (= i j)
          (let ((s (pour-action state caps i j)))
            (unless (equal s state)
              (let ((amount-transferred
                     (- (nth i state) (nth i s)))) ; compute transfer for human description
                (when (> amount-transferred 0)
                  (push (cons s (format nil "Pour ~A -> ~A (~A)" i j amount-transferred)) result))))))))
    ;; return list in stable order
    (nreverse result)))

(defun reconstruct-path (came-from goal-key)
  "Reconstruct path (list of (action . state)) from came-from hash-table and goal-key.
came-from maps state-key -> (parent-key . action), initial state's parent is nil."
  (let ((path nil)
        (cur-key goal-key))
    (loop while cur-key do
         (let ((entry (gethash cur-key came-from)))
           (when (null entry)
             (push (cons "Start" (read-from-string cur-key)) path) ; shouldn't normally happen
             (setf cur-key nil)
             (return))
           (let ((parent (car entry))
                 (action (cdr entry)))
             ;; parse cur-key into state list for the path element
             (push (cons action (read-from-string cur-key)) path)
             (setf cur-key parent))))
    ;; path currently includes the goal-state action as last step; first element is the action that produced that state
    ;; We want the path beginning from initial state's action (or "Start").
    ;; The first element's action corresponds to the move that produced that state; that's fine for display.
    path))

(defun solve-jugs (caps target &optional (start-state nil))
  "Solve the jugs problem with capacities CAPS (list of positive ints) and TARGET (int).
START-STATE defaults to all zeros. Returns a list of (action . state) pairs from start -> goal,
or NIL if no solution."
  (let* ((n (length caps))
         (start (or start-state (make-list n :initial-element 0)))
         (start-key (state->key start)))
    (when (goal-reached-p start target)
      (return-from solve-jugs (list (cons "Start" start))))
    (let ((queue (list start))
          (came-from (make-hash-table :test #'equal)) ; key -> (parent-key . action)
          (visited (make-hash-table :test #'equal)))
      (setf (gethash start-key came-from) nil) ; start has no parent
      (setf (gethash start-key visited) t)
      (loop while queue do
           (let* ((state (pop queue))
                  (state-key (state->key state)))
             (when (goal-reached-p state target)
               ;; reconstruct path
               (let ((path (reconstruct-path came-from state-key)))
                 (return-from solve-jugs path)))
             ;; expand neighbors
             (dolist (pair (neighbors-with-actions state caps))
               (let* ((new-state (car pair))
                      (action (cdr pair))
                      (new-key (state->key new-state)))
                 (unless (gethash new-key visited)
                   (setf (gethash new-key visited) t)
                   (setf (gethash new-key came-from) (cons state-key action))
                   (push new-state queue))))))
      ;; if queue empties
      nil)))

(defun pretty-print-solution (solution)
  "Print the solution (list of (action . state))."
  (if (null solution)
      (format t "No solution found.~%")
      (progn
        (format t "Solution (~A steps):~%" (1- (length solution))) ; first element might be Start or first action
        (loop for pair in solution
              for step from 0 do
              (let ((action (car pair))
                    (state (cdr pair)))
                (format t "~2D: ~A -> ~A~%" step action state))))))

;;; Example usage:
; (let ((sol (solve-jugs '(8 5 3) 4)))
;   (pretty-print-solution sol))