; Auto-generated. Do not edit!


(cl:in-package am_msgs-msg)


;//! \htmlinclude CurrentStatus.msg.html

(cl:defclass <CurrentStatus> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (state
    :reader state
    :initarg :state
    :type cl:fixnum
    :initform 0)
   (subState
    :reader subState
    :initarg :subState
    :type cl:fixnum
    :initform 0)
   (mode
    :reader mode
    :initarg :mode
    :type cl:fixnum
    :initform 0))
)

(cl:defclass CurrentStatus (<CurrentStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <CurrentStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'CurrentStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_msgs-msg:<CurrentStatus> is deprecated: use am_msgs-msg:CurrentStatus instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <CurrentStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:header-val is deprecated.  Use am_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <CurrentStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:state-val is deprecated.  Use am_msgs-msg:state instead.")
  (state m))

(cl:ensure-generic-function 'subState-val :lambda-list '(m))
(cl:defmethod subState-val ((m <CurrentStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:subState-val is deprecated.  Use am_msgs-msg:subState instead.")
  (subState m))

(cl:ensure-generic-function 'mode-val :lambda-list '(m))
(cl:defmethod mode-val ((m <CurrentStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:mode-val is deprecated.  Use am_msgs-msg:mode instead.")
  (mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <CurrentStatus>) ostream)
  "Serializes a message object of type '<CurrentStatus>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'subState)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'mode)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <CurrentStatus>) istream)
  "Deserializes a message object of type '<CurrentStatus>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'subState) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mode) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<CurrentStatus>)))
  "Returns string type for a message object of type '<CurrentStatus>"
  "am_msgs/CurrentStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'CurrentStatus)))
  "Returns string type for a message object of type 'CurrentStatus"
  "am_msgs/CurrentStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<CurrentStatus>)))
  "Returns md5sum for a message object of type '<CurrentStatus>"
  "3c9ffe94e8f0a9d6014780d8cebb049b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'CurrentStatus)))
  "Returns md5sum for a message object of type 'CurrentStatus"
  "3c9ffe94e8f0a9d6014780d8cebb049b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<CurrentStatus>)))
  "Returns full string definition for message of type '<CurrentStatus>"
  (cl:format cl:nil "# Topic that is meant to reflect contents of command family \"CurrentStatus\" with command \"GetStatusKeepAlive\" from Automower TIF~%~%Header header~%~%# -1 = undefined~%# 0 = Power-up state~%# 1 = Waiting state~%# 2 = Irregular cutting state~%# 3 = Searching CS state~%# 4 = Charging state~%# 5 = Leaving CS state~%# 6 = SW downloading state~%# 7 = Fault state. Fatal Error~%# 8 = Fault state. Error~%int16 state~%~%# -1 = undefined~%# 0 = No sub status~%# 1 = Irregular moving~%# 2 = Complex outside~%# 3 = Complex wheels blocked~%# 4 = Complex wheels slipped~%# 5 = Complex outside at reverse~%# 6 = Complex collision~%# 7 = Complex lifted~%# 8 = Local intensive cutting~%# 9 = Follow guide wire 1 in~%# 10 = Follow right boundary wire in~%# 11 = Docking~%# 12 = Fast charging~%# 13 = Top-up charging~%# 14 = Charging ready~%# 15 = Exit angle~%# 16 = Follow guide wire 1 out~%# 17 = Follow right boundary wire out~%# 18 = Complex No Loop Signal~%# 19 = Complex Cutting Means blocked~%# 20 = Complex Cutting Means blocked~%# 21 = Follow guide wire 2 in~%# 22 = Follow guide wire 3 in~%# 23 = Follow guide wire 2 out~%# 24 = Follow guide wire 3 out~%# 25 = Follow left boundary wire in~%# 26 = Follow left boundary wire out~%# 27 = Complex too steep slope~%int16 subState~%~%# -1 = undefined~%# 0 = Power-down mode~%# 1 = Standby mode~%# 2 = Sleep mode~%# 3 = Sub -active mode~%# 4 = Boot mode~%# 5 = Idle mode~%# 6 = Auto mode~%# 7 = Manual mode~%# 8 = Home mode~%int16 mode~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'CurrentStatus)))
  "Returns full string definition for message of type 'CurrentStatus"
  (cl:format cl:nil "# Topic that is meant to reflect contents of command family \"CurrentStatus\" with command \"GetStatusKeepAlive\" from Automower TIF~%~%Header header~%~%# -1 = undefined~%# 0 = Power-up state~%# 1 = Waiting state~%# 2 = Irregular cutting state~%# 3 = Searching CS state~%# 4 = Charging state~%# 5 = Leaving CS state~%# 6 = SW downloading state~%# 7 = Fault state. Fatal Error~%# 8 = Fault state. Error~%int16 state~%~%# -1 = undefined~%# 0 = No sub status~%# 1 = Irregular moving~%# 2 = Complex outside~%# 3 = Complex wheels blocked~%# 4 = Complex wheels slipped~%# 5 = Complex outside at reverse~%# 6 = Complex collision~%# 7 = Complex lifted~%# 8 = Local intensive cutting~%# 9 = Follow guide wire 1 in~%# 10 = Follow right boundary wire in~%# 11 = Docking~%# 12 = Fast charging~%# 13 = Top-up charging~%# 14 = Charging ready~%# 15 = Exit angle~%# 16 = Follow guide wire 1 out~%# 17 = Follow right boundary wire out~%# 18 = Complex No Loop Signal~%# 19 = Complex Cutting Means blocked~%# 20 = Complex Cutting Means blocked~%# 21 = Follow guide wire 2 in~%# 22 = Follow guide wire 3 in~%# 23 = Follow guide wire 2 out~%# 24 = Follow guide wire 3 out~%# 25 = Follow left boundary wire in~%# 26 = Follow left boundary wire out~%# 27 = Complex too steep slope~%int16 subState~%~%# -1 = undefined~%# 0 = Power-down mode~%# 1 = Standby mode~%# 2 = Sleep mode~%# 3 = Sub -active mode~%# 4 = Boot mode~%# 5 = Idle mode~%# 6 = Auto mode~%# 7 = Manual mode~%# 8 = Home mode~%int16 mode~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <CurrentStatus>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <CurrentStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'CurrentStatus
    (cl:cons ':header (header msg))
    (cl:cons ':state (state msg))
    (cl:cons ':subState (subState msg))
    (cl:cons ':mode (mode msg))
))
