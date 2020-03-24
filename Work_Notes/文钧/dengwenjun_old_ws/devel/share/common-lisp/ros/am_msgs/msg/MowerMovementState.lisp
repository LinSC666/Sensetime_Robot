; Auto-generated. Do not edit!


(cl:in-package am_msgs-msg)


;//! \htmlinclude MowerMovementState.msg.html

(cl:defclass <MowerMovementState> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (state
    :reader state
    :initarg :state
    :type cl:fixnum
    :initform 0))
)

(cl:defclass MowerMovementState (<MowerMovementState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MowerMovementState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MowerMovementState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_msgs-msg:<MowerMovementState> is deprecated: use am_msgs-msg:MowerMovementState instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MowerMovementState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:header-val is deprecated.  Use am_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <MowerMovementState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:state-val is deprecated.  Use am_msgs-msg:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MowerMovementState>) ostream)
  "Serializes a message object of type '<MowerMovementState>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'state)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MowerMovementState>) istream)
  "Deserializes a message object of type '<MowerMovementState>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MowerMovementState>)))
  "Returns string type for a message object of type '<MowerMovementState>"
  "am_msgs/MowerMovementState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MowerMovementState)))
  "Returns string type for a message object of type 'MowerMovementState"
  "am_msgs/MowerMovementState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MowerMovementState>)))
  "Returns md5sum for a message object of type '<MowerMovementState>"
  "1951e0c38e32ff876c61f0bfad87a62d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MowerMovementState)))
  "Returns md5sum for a message object of type 'MowerMovementState"
  "1951e0c38e32ff876c61f0bfad87a62d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MowerMovementState>)))
  "Returns full string definition for message of type '<MowerMovementState>"
  (cl:format cl:nil "Header header~%~%# -1 = undefined~%# 0 = Forward~%# 1 = Pause~%# 2 = TurnLeft~%# 3 = TurnRight~%int16 state~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MowerMovementState)))
  "Returns full string definition for message of type 'MowerMovementState"
  (cl:format cl:nil "Header header~%~%# -1 = undefined~%# 0 = Forward~%# 1 = Pause~%# 2 = TurnLeft~%# 3 = TurnRight~%int16 state~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MowerMovementState>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MowerMovementState>))
  "Converts a ROS message object to a list"
  (cl:list 'MowerMovementState
    (cl:cons ':header (header msg))
    (cl:cons ':state (state msg))
))
