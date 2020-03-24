;; Auto-generated. Do not edit!


(when (boundp 'am_msgs::MowerMovementState)
  (if (not (find-package "AM_MSGS"))
    (make-package "AM_MSGS"))
  (shadow 'MowerMovementState (find-package "AM_MSGS")))
(unless (find-package "AM_MSGS::MOWERMOVEMENTSTATE")
  (make-package "AM_MSGS::MOWERMOVEMENTSTATE"))

(in-package "ROS")
;;//! \htmlinclude MowerMovementState.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass am_msgs::MowerMovementState
  :super ros::object
  :slots (_header _state ))

(defmethod am_msgs::MowerMovementState
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:state __state) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _state (round __state))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:state
   (&optional __state)
   (if __state (setq _state __state)) _state)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int16 _state
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int16 _state
       (write-word _state s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int16 _state
     (setq _state (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get am_msgs::MowerMovementState :md5sum-) "1951e0c38e32ff876c61f0bfad87a62d")
(setf (get am_msgs::MowerMovementState :datatype-) "am_msgs/MowerMovementState")
(setf (get am_msgs::MowerMovementState :definition-)
      "Header header

# -1 = undefined
# 0 = Forward
# 1 = Pause
# 2 = TurnLeft
# 3 = TurnRight
int16 state

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



(provide :am_msgs/MowerMovementState "1951e0c38e32ff876c61f0bfad87a62d")


