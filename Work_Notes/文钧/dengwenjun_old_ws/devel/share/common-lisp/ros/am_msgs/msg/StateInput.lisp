; Auto-generated. Do not edit!


(cl:in-package am_msgs-msg)


;//! \htmlinclude StateInput.msg.html

(cl:defclass <StateInput> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (pathSegmentationBlocked
    :reader pathSegmentationBlocked
    :initarg :pathSegmentationBlocked
    :type cl:boolean
    :initform cl:nil)
   (pathDetectionBlocked
    :reader pathDetectionBlocked
    :initarg :pathDetectionBlocked
    :type cl:boolean
    :initform cl:nil)
   (turningDirectionLeft
    :reader turningDirectionLeft
    :initarg :turningDirectionLeft
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass StateInput (<StateInput>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <StateInput>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'StateInput)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_msgs-msg:<StateInput> is deprecated: use am_msgs-msg:StateInput instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <StateInput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:header-val is deprecated.  Use am_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'pathSegmentationBlocked-val :lambda-list '(m))
(cl:defmethod pathSegmentationBlocked-val ((m <StateInput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:pathSegmentationBlocked-val is deprecated.  Use am_msgs-msg:pathSegmentationBlocked instead.")
  (pathSegmentationBlocked m))

(cl:ensure-generic-function 'pathDetectionBlocked-val :lambda-list '(m))
(cl:defmethod pathDetectionBlocked-val ((m <StateInput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:pathDetectionBlocked-val is deprecated.  Use am_msgs-msg:pathDetectionBlocked instead.")
  (pathDetectionBlocked m))

(cl:ensure-generic-function 'turningDirectionLeft-val :lambda-list '(m))
(cl:defmethod turningDirectionLeft-val ((m <StateInput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:turningDirectionLeft-val is deprecated.  Use am_msgs-msg:turningDirectionLeft instead.")
  (turningDirectionLeft m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <StateInput>) ostream)
  "Serializes a message object of type '<StateInput>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pathSegmentationBlocked) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'pathDetectionBlocked) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'turningDirectionLeft) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <StateInput>) istream)
  "Deserializes a message object of type '<StateInput>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:slot-value msg 'pathSegmentationBlocked) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'pathDetectionBlocked) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'turningDirectionLeft) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<StateInput>)))
  "Returns string type for a message object of type '<StateInput>"
  "am_msgs/StateInput")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'StateInput)))
  "Returns string type for a message object of type 'StateInput"
  "am_msgs/StateInput")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<StateInput>)))
  "Returns md5sum for a message object of type '<StateInput>"
  "66f3e8700901a4c81c50fee4c374e6c7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'StateInput)))
  "Returns md5sum for a message object of type 'StateInput"
  "66f3e8700901a4c81c50fee4c374e6c7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<StateInput>)))
  "Returns full string definition for message of type '<StateInput>"
  (cl:format cl:nil "Header header~%bool pathSegmentationBlocked~%bool pathDetectionBlocked~%bool turningDirectionLeft~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'StateInput)))
  "Returns full string definition for message of type 'StateInput"
  (cl:format cl:nil "Header header~%bool pathSegmentationBlocked~%bool pathDetectionBlocked~%bool turningDirectionLeft~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <StateInput>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <StateInput>))
  "Converts a ROS message object to a list"
  (cl:list 'StateInput
    (cl:cons ':header (header msg))
    (cl:cons ':pathSegmentationBlocked (pathSegmentationBlocked msg))
    (cl:cons ':pathDetectionBlocked (pathDetectionBlocked msg))
    (cl:cons ':turningDirectionLeft (turningDirectionLeft msg))
))
