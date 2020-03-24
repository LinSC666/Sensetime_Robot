;; Auto-generated. Do not edit!


(when (boundp 'am_msgs::StateInput)
  (if (not (find-package "AM_MSGS"))
    (make-package "AM_MSGS"))
  (shadow 'StateInput (find-package "AM_MSGS")))
(unless (find-package "AM_MSGS::STATEINPUT")
  (make-package "AM_MSGS::STATEINPUT"))

(in-package "ROS")
;;//! \htmlinclude StateInput.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass am_msgs::StateInput
  :super ros::object
  :slots (_header _pathSegmentationBlocked _pathDetectionBlocked _turningDirectionLeft ))

(defmethod am_msgs::StateInput
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:pathSegmentationBlocked __pathSegmentationBlocked) nil)
    ((:pathDetectionBlocked __pathDetectionBlocked) nil)
    ((:turningDirectionLeft __turningDirectionLeft) nil)
    )
   (send-super :init)
   (setq _header __header)
   (setq _pathSegmentationBlocked __pathSegmentationBlocked)
   (setq _pathDetectionBlocked __pathDetectionBlocked)
   (setq _turningDirectionLeft __turningDirectionLeft)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:pathSegmentationBlocked
   (&optional __pathSegmentationBlocked)
   (if __pathSegmentationBlocked (setq _pathSegmentationBlocked __pathSegmentationBlocked)) _pathSegmentationBlocked)
  (:pathDetectionBlocked
   (&optional __pathDetectionBlocked)
   (if __pathDetectionBlocked (setq _pathDetectionBlocked __pathDetectionBlocked)) _pathDetectionBlocked)
  (:turningDirectionLeft
   (&optional __turningDirectionLeft)
   (if __turningDirectionLeft (setq _turningDirectionLeft __turningDirectionLeft)) _turningDirectionLeft)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; bool _pathSegmentationBlocked
    1
    ;; bool _pathDetectionBlocked
    1
    ;; bool _turningDirectionLeft
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; bool _pathSegmentationBlocked
       (if _pathSegmentationBlocked (write-byte -1 s) (write-byte 0 s))
     ;; bool _pathDetectionBlocked
       (if _pathDetectionBlocked (write-byte -1 s) (write-byte 0 s))
     ;; bool _turningDirectionLeft
       (if _turningDirectionLeft (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; bool _pathSegmentationBlocked
     (setq _pathSegmentationBlocked (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _pathDetectionBlocked
     (setq _pathDetectionBlocked (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;; bool _turningDirectionLeft
     (setq _turningDirectionLeft (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get am_msgs::StateInput :md5sum-) "66f3e8700901a4c81c50fee4c374e6c7")
(setf (get am_msgs::StateInput :datatype-) "am_msgs/StateInput")
(setf (get am_msgs::StateInput :definition-)
      "Header header
bool pathSegmentationBlocked
bool pathDetectionBlocked
bool turningDirectionLeft
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

")



(provide :am_msgs/StateInput "66f3e8700901a4c81c50fee4c374e6c7")


