;; Auto-generated. Do not edit!


(when (boundp 'am_driver_safe::turnOfLoopCmd)
  (if (not (find-package "AM_DRIVER_SAFE"))
    (make-package "AM_DRIVER_SAFE"))
  (shadow 'turnOfLoopCmd (find-package "AM_DRIVER_SAFE")))
(unless (find-package "AM_DRIVER_SAFE::TURNOFLOOPCMD")
  (make-package "AM_DRIVER_SAFE::TURNOFLOOPCMD"))
(unless (find-package "AM_DRIVER_SAFE::TURNOFLOOPCMDREQUEST")
  (make-package "AM_DRIVER_SAFE::TURNOFLOOPCMDREQUEST"))
(unless (find-package "AM_DRIVER_SAFE::TURNOFLOOPCMDRESPONSE")
  (make-package "AM_DRIVER_SAFE::TURNOFLOOPCMDRESPONSE"))

(in-package "ROS")





(defclass am_driver_safe::turnOfLoopCmdRequest
  :super ros::object
  :slots ())

(defmethod am_driver_safe::turnOfLoopCmdRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass am_driver_safe::turnOfLoopCmdResponse
  :super ros::object
  :slots ())

(defmethod am_driver_safe::turnOfLoopCmdResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass am_driver_safe::turnOfLoopCmd
  :super ros::object
  :slots ())

(setf (get am_driver_safe::turnOfLoopCmd :md5sum-) "d41d8cd98f00b204e9800998ecf8427e")
(setf (get am_driver_safe::turnOfLoopCmd :datatype-) "am_driver_safe/turnOfLoopCmd")
(setf (get am_driver_safe::turnOfLoopCmd :request) am_driver_safe::turnOfLoopCmdRequest)
(setf (get am_driver_safe::turnOfLoopCmd :response) am_driver_safe::turnOfLoopCmdResponse)

(defmethod am_driver_safe::turnOfLoopCmdRequest
  (:response () (instance am_driver_safe::turnOfLoopCmdResponse :init)))

(setf (get am_driver_safe::turnOfLoopCmdRequest :md5sum-) "d41d8cd98f00b204e9800998ecf8427e")
(setf (get am_driver_safe::turnOfLoopCmdRequest :datatype-) "am_driver_safe/turnOfLoopCmdRequest")
(setf (get am_driver_safe::turnOfLoopCmdRequest :definition-)
      "---

")

(setf (get am_driver_safe::turnOfLoopCmdResponse :md5sum-) "d41d8cd98f00b204e9800998ecf8427e")
(setf (get am_driver_safe::turnOfLoopCmdResponse :datatype-) "am_driver_safe/turnOfLoopCmdResponse")
(setf (get am_driver_safe::turnOfLoopCmdResponse :definition-)
      "---

")



(provide :am_driver_safe/turnOfLoopCmd "d41d8cd98f00b204e9800998ecf8427e")


