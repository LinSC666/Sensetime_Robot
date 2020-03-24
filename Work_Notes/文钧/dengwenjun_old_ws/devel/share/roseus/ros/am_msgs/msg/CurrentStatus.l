;; Auto-generated. Do not edit!


(when (boundp 'am_msgs::CurrentStatus)
  (if (not (find-package "AM_MSGS"))
    (make-package "AM_MSGS"))
  (shadow 'CurrentStatus (find-package "AM_MSGS")))
(unless (find-package "AM_MSGS::CURRENTSTATUS")
  (make-package "AM_MSGS::CURRENTSTATUS"))

(in-package "ROS")
;;//! \htmlinclude CurrentStatus.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass am_msgs::CurrentStatus
  :super ros::object
  :slots (_header _state _subState _mode ))

(defmethod am_msgs::CurrentStatus
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:state __state) 0)
    ((:subState __subState) 0)
    ((:mode __mode) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _state (round __state))
   (setq _subState (round __subState))
   (setq _mode (round __mode))
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
  (:subState
   (&optional __subState)
   (if __subState (setq _subState __subState)) _subState)
  (:mode
   (&optional __mode)
   (if __mode (setq _mode __mode)) _mode)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int16 _state
    2
    ;; int16 _subState
    2
    ;; int16 _mode
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
     ;; int16 _subState
       (write-word _subState s)
     ;; int16 _mode
       (write-word _mode s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int16 _state
     (setq _state (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _subState
     (setq _subState (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _mode
     (setq _mode (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get am_msgs::CurrentStatus :md5sum-) "3c9ffe94e8f0a9d6014780d8cebb049b")
(setf (get am_msgs::CurrentStatus :datatype-) "am_msgs/CurrentStatus")
(setf (get am_msgs::CurrentStatus :definition-)
      "# Topic that is meant to reflect contents of command family \"CurrentStatus\" with command \"GetStatusKeepAlive\" from Automower TIF

Header header

# -1 = undefined
# 0 = Power-up state
# 1 = Waiting state
# 2 = Irregular cutting state
# 3 = Searching CS state
# 4 = Charging state
# 5 = Leaving CS state
# 6 = SW downloading state
# 7 = Fault state. Fatal Error
# 8 = Fault state. Error
int16 state

# -1 = undefined
# 0 = No sub status
# 1 = Irregular moving
# 2 = Complex outside
# 3 = Complex wheels blocked
# 4 = Complex wheels slipped
# 5 = Complex outside at reverse
# 6 = Complex collision
# 7 = Complex lifted
# 8 = Local intensive cutting
# 9 = Follow guide wire 1 in
# 10 = Follow right boundary wire in
# 11 = Docking
# 12 = Fast charging
# 13 = Top-up charging
# 14 = Charging ready
# 15 = Exit angle
# 16 = Follow guide wire 1 out
# 17 = Follow right boundary wire out
# 18 = Complex No Loop Signal
# 19 = Complex Cutting Means blocked
# 20 = Complex Cutting Means blocked
# 21 = Follow guide wire 2 in
# 22 = Follow guide wire 3 in
# 23 = Follow guide wire 2 out
# 24 = Follow guide wire 3 out
# 25 = Follow left boundary wire in
# 26 = Follow left boundary wire out
# 27 = Complex too steep slope
int16 subState

# -1 = undefined
# 0 = Power-down mode
# 1 = Standby mode
# 2 = Sleep mode
# 3 = Sub -active mode
# 4 = Boot mode
# 5 = Idle mode
# 6 = Auto mode
# 7 = Manual mode
# 8 = Home mode
int16 mode

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



(provide :am_msgs/CurrentStatus "3c9ffe94e8f0a9d6014780d8cebb049b")


