; Auto-generated. Do not edit!


(cl:in-package am_msgs-msg)


;//! \htmlinclude Loop.msg.html

(cl:defclass <Loop> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (frontCenter
    :reader frontCenter
    :initarg :frontCenter
    :type cl:integer
    :initform 0)
   (frontRight
    :reader frontRight
    :initarg :frontRight
    :type cl:integer
    :initform 0)
   (rearLeft
    :reader rearLeft
    :initarg :rearLeft
    :type cl:integer
    :initform 0)
   (rearRight
    :reader rearRight
    :initarg :rearRight
    :type cl:integer
    :initform 0)
   (A0
    :reader A0
    :initarg :A0
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (N
    :reader N
    :initarg :N
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (F
    :reader F
    :initarg :F
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (G1
    :reader G1
    :initarg :G1
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (G2
    :reader G2
    :initarg :G2
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (G3
    :reader G3
    :initarg :G3
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (QA0
    :reader QA0
    :initarg :QA0
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (QF
    :reader QF
    :initarg :QF
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData))
   (QN
    :reader QN
    :initarg :QN
    :type am_msgs-msg:LoopData
    :initform (cl:make-instance 'am_msgs-msg:LoopData)))
)

(cl:defclass Loop (<Loop>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Loop>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Loop)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_msgs-msg:<Loop> is deprecated: use am_msgs-msg:Loop instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:header-val is deprecated.  Use am_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'frontCenter-val :lambda-list '(m))
(cl:defmethod frontCenter-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:frontCenter-val is deprecated.  Use am_msgs-msg:frontCenter instead.")
  (frontCenter m))

(cl:ensure-generic-function 'frontRight-val :lambda-list '(m))
(cl:defmethod frontRight-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:frontRight-val is deprecated.  Use am_msgs-msg:frontRight instead.")
  (frontRight m))

(cl:ensure-generic-function 'rearLeft-val :lambda-list '(m))
(cl:defmethod rearLeft-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:rearLeft-val is deprecated.  Use am_msgs-msg:rearLeft instead.")
  (rearLeft m))

(cl:ensure-generic-function 'rearRight-val :lambda-list '(m))
(cl:defmethod rearRight-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:rearRight-val is deprecated.  Use am_msgs-msg:rearRight instead.")
  (rearRight m))

(cl:ensure-generic-function 'A0-val :lambda-list '(m))
(cl:defmethod A0-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:A0-val is deprecated.  Use am_msgs-msg:A0 instead.")
  (A0 m))

(cl:ensure-generic-function 'N-val :lambda-list '(m))
(cl:defmethod N-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:N-val is deprecated.  Use am_msgs-msg:N instead.")
  (N m))

(cl:ensure-generic-function 'F-val :lambda-list '(m))
(cl:defmethod F-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:F-val is deprecated.  Use am_msgs-msg:F instead.")
  (F m))

(cl:ensure-generic-function 'G1-val :lambda-list '(m))
(cl:defmethod G1-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:G1-val is deprecated.  Use am_msgs-msg:G1 instead.")
  (G1 m))

(cl:ensure-generic-function 'G2-val :lambda-list '(m))
(cl:defmethod G2-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:G2-val is deprecated.  Use am_msgs-msg:G2 instead.")
  (G2 m))

(cl:ensure-generic-function 'G3-val :lambda-list '(m))
(cl:defmethod G3-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:G3-val is deprecated.  Use am_msgs-msg:G3 instead.")
  (G3 m))

(cl:ensure-generic-function 'QA0-val :lambda-list '(m))
(cl:defmethod QA0-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:QA0-val is deprecated.  Use am_msgs-msg:QA0 instead.")
  (QA0 m))

(cl:ensure-generic-function 'QF-val :lambda-list '(m))
(cl:defmethod QF-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:QF-val is deprecated.  Use am_msgs-msg:QF instead.")
  (QF m))

(cl:ensure-generic-function 'QN-val :lambda-list '(m))
(cl:defmethod QN-val ((m <Loop>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:QN-val is deprecated.  Use am_msgs-msg:QN instead.")
  (QN m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Loop>) ostream)
  "Serializes a message object of type '<Loop>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'frontCenter)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'frontRight)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rearLeft)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rearRight)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'A0) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'N) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'F) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'G1) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'G2) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'G3) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'QA0) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'QF) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'QN) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Loop>) istream)
  "Deserializes a message object of type '<Loop>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frontCenter) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'frontRight) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rearLeft) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rearRight) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'A0) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'N) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'F) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'G1) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'G2) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'G3) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'QA0) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'QF) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'QN) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Loop>)))
  "Returns string type for a message object of type '<Loop>"
  "am_msgs/Loop")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Loop)))
  "Returns string type for a message object of type 'Loop"
  "am_msgs/Loop")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Loop>)))
  "Returns md5sum for a message object of type '<Loop>"
  "92ab15532a8fc5e195e713df1d41a4bf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Loop)))
  "Returns md5sum for a message object of type 'Loop"
  "92ab15532a8fc5e195e713df1d41a4bf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Loop>)))
  "Returns full string definition for message of type '<Loop>"
  (cl:format cl:nil "Header header~%int32 frontCenter~%int32 frontRight~%int32 rearLeft~%int32 rearRight~%LoopData A0~%LoopData N~%LoopData F~%LoopData G1~%LoopData G2~%LoopData G3~%LoopData QA0~%LoopData QF~%LoopData QN ~% ~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: am_msgs/LoopData~%int32 frontCenter~%int32 frontRight~%int32 rearLeft~%int32 rearRight~% ~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Loop)))
  "Returns full string definition for message of type 'Loop"
  (cl:format cl:nil "Header header~%int32 frontCenter~%int32 frontRight~%int32 rearLeft~%int32 rearRight~%LoopData A0~%LoopData N~%LoopData F~%LoopData G1~%LoopData G2~%LoopData G3~%LoopData QA0~%LoopData QF~%LoopData QN ~% ~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: am_msgs/LoopData~%int32 frontCenter~%int32 frontRight~%int32 rearLeft~%int32 rearRight~% ~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Loop>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'A0))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'N))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'F))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'G1))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'G2))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'G3))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'QA0))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'QF))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'QN))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Loop>))
  "Converts a ROS message object to a list"
  (cl:list 'Loop
    (cl:cons ':header (header msg))
    (cl:cons ':frontCenter (frontCenter msg))
    (cl:cons ':frontRight (frontRight msg))
    (cl:cons ':rearLeft (rearLeft msg))
    (cl:cons ':rearRight (rearRight msg))
    (cl:cons ':A0 (A0 msg))
    (cl:cons ':N (N msg))
    (cl:cons ':F (F msg))
    (cl:cons ':G1 (G1 msg))
    (cl:cons ':G2 (G2 msg))
    (cl:cons ':G3 (G3 msg))
    (cl:cons ':QA0 (QA0 msg))
    (cl:cons ':QF (QF msg))
    (cl:cons ':QN (QN msg))
))
