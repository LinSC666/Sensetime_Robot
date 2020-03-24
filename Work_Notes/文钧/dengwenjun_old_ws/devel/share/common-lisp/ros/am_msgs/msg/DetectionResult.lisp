; Auto-generated. Do not edit!


(cl:in-package am_msgs-msg)


;//! \htmlinclude DetectionResult.msg.html

(cl:defclass <DetectionResult> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (objects
    :reader objects
    :initarg :objects
    :type (cl:vector am_msgs-msg:Object)
   :initform (cl:make-array 0 :element-type 'am_msgs-msg:Object :initial-element (cl:make-instance 'am_msgs-msg:Object))))
)

(cl:defclass DetectionResult (<DetectionResult>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DetectionResult>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DetectionResult)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_msgs-msg:<DetectionResult> is deprecated: use am_msgs-msg:DetectionResult instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <DetectionResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:header-val is deprecated.  Use am_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'objects-val :lambda-list '(m))
(cl:defmethod objects-val ((m <DetectionResult>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:objects-val is deprecated.  Use am_msgs-msg:objects instead.")
  (objects m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DetectionResult>) ostream)
  "Serializes a message object of type '<DetectionResult>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'objects))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'objects))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DetectionResult>) istream)
  "Deserializes a message object of type '<DetectionResult>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'objects) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'objects)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'am_msgs-msg:Object))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DetectionResult>)))
  "Returns string type for a message object of type '<DetectionResult>"
  "am_msgs/DetectionResult")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DetectionResult)))
  "Returns string type for a message object of type 'DetectionResult"
  "am_msgs/DetectionResult")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DetectionResult>)))
  "Returns md5sum for a message object of type '<DetectionResult>"
  "d05414622f3f3b983211d67b7ce383ac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DetectionResult)))
  "Returns md5sum for a message object of type 'DetectionResult"
  "d05414622f3f3b983211d67b7ce383ac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DetectionResult>)))
  "Returns full string definition for message of type '<DetectionResult>"
  (cl:format cl:nil "Header header~%~%Object[] objects~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: am_msgs/Object~%int32 object_index~%float32 confidence # A value between 0.0 and 1.0.~%Rect bounding_box_cv # A bounding box on the camera coordinate.~%geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.~%uint8 label~%uint8 LABEL_UNKNOWN=0~%uint8 LABEL_PEDESTRIAN=1~%uint8 LABEL_CONE=2~%uint8 LABEL_GOLF=3~%uint8 LABEL_SPRINKLER=4~%~%================================================================================~%MSG: am_msgs/Rect~%float32 x~%float32 y~%float32 width~%float32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DetectionResult)))
  "Returns full string definition for message of type 'DetectionResult"
  (cl:format cl:nil "Header header~%~%Object[] objects~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: am_msgs/Object~%int32 object_index~%float32 confidence # A value between 0.0 and 1.0.~%Rect bounding_box_cv # A bounding box on the camera coordinate.~%geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.~%uint8 label~%uint8 LABEL_UNKNOWN=0~%uint8 LABEL_PEDESTRIAN=1~%uint8 LABEL_CONE=2~%uint8 LABEL_GOLF=3~%uint8 LABEL_SPRINKLER=4~%~%================================================================================~%MSG: am_msgs/Rect~%float32 x~%float32 y~%float32 width~%float32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DetectionResult>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'objects) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DetectionResult>))
  "Converts a ROS message object to a list"
  (cl:list 'DetectionResult
    (cl:cons ':header (header msg))
    (cl:cons ':objects (objects msg))
))
