; Auto-generated. Do not edit!


(cl:in-package am_msgs-msg)


;//! \htmlinclude Object.msg.html

(cl:defclass <Object> (roslisp-msg-protocol:ros-message)
  ((object_index
    :reader object_index
    :initarg :object_index
    :type cl:integer
    :initform 0)
   (confidence
    :reader confidence
    :initarg :confidence
    :type cl:float
    :initform 0.0)
   (bounding_box_cv
    :reader bounding_box_cv
    :initarg :bounding_box_cv
    :type am_msgs-msg:Rect
    :initform (cl:make-instance 'am_msgs-msg:Rect))
   (location_bv
    :reader location_bv
    :initarg :location_bv
    :type (cl:vector geometry_msgs-msg:Point)
   :initform (cl:make-array 0 :element-type 'geometry_msgs-msg:Point :initial-element (cl:make-instance 'geometry_msgs-msg:Point)))
   (label
    :reader label
    :initarg :label
    :type cl:fixnum
    :initform 0))
)

(cl:defclass Object (<Object>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Object>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Object)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name am_msgs-msg:<Object> is deprecated: use am_msgs-msg:Object instead.")))

(cl:ensure-generic-function 'object_index-val :lambda-list '(m))
(cl:defmethod object_index-val ((m <Object>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:object_index-val is deprecated.  Use am_msgs-msg:object_index instead.")
  (object_index m))

(cl:ensure-generic-function 'confidence-val :lambda-list '(m))
(cl:defmethod confidence-val ((m <Object>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:confidence-val is deprecated.  Use am_msgs-msg:confidence instead.")
  (confidence m))

(cl:ensure-generic-function 'bounding_box_cv-val :lambda-list '(m))
(cl:defmethod bounding_box_cv-val ((m <Object>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:bounding_box_cv-val is deprecated.  Use am_msgs-msg:bounding_box_cv instead.")
  (bounding_box_cv m))

(cl:ensure-generic-function 'location_bv-val :lambda-list '(m))
(cl:defmethod location_bv-val ((m <Object>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:location_bv-val is deprecated.  Use am_msgs-msg:location_bv instead.")
  (location_bv m))

(cl:ensure-generic-function 'label-val :lambda-list '(m))
(cl:defmethod label-val ((m <Object>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader am_msgs-msg:label-val is deprecated.  Use am_msgs-msg:label instead.")
  (label m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<Object>)))
    "Constants for message type '<Object>"
  '((:LABEL_UNKNOWN . 0)
    (:LABEL_PEDESTRIAN . 1)
    (:LABEL_CONE . 2)
    (:LABEL_GOLF . 3)
    (:LABEL_SPRINKLER . 4))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'Object)))
    "Constants for message type 'Object"
  '((:LABEL_UNKNOWN . 0)
    (:LABEL_PEDESTRIAN . 1)
    (:LABEL_CONE . 2)
    (:LABEL_GOLF . 3)
    (:LABEL_SPRINKLER . 4))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Object>) ostream)
  "Serializes a message object of type '<Object>"
  (cl:let* ((signed (cl:slot-value msg 'object_index)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'confidence))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bounding_box_cv) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'location_bv))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'location_bv))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'label)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Object>) istream)
  "Deserializes a message object of type '<Object>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'object_index) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'confidence) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bounding_box_cv) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'location_bv) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'location_bv)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'geometry_msgs-msg:Point))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'label)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Object>)))
  "Returns string type for a message object of type '<Object>"
  "am_msgs/Object")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Object)))
  "Returns string type for a message object of type 'Object"
  "am_msgs/Object")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Object>)))
  "Returns md5sum for a message object of type '<Object>"
  "0c9b334f865e3aab40d33e895236278a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Object)))
  "Returns md5sum for a message object of type 'Object"
  "0c9b334f865e3aab40d33e895236278a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Object>)))
  "Returns full string definition for message of type '<Object>"
  (cl:format cl:nil "int32 object_index~%float32 confidence # A value between 0.0 and 1.0.~%Rect bounding_box_cv # A bounding box on the camera coordinate.~%geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.~%uint8 label~%uint8 LABEL_UNKNOWN=0~%uint8 LABEL_PEDESTRIAN=1~%uint8 LABEL_CONE=2~%uint8 LABEL_GOLF=3~%uint8 LABEL_SPRINKLER=4~%~%================================================================================~%MSG: am_msgs/Rect~%float32 x~%float32 y~%float32 width~%float32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Object)))
  "Returns full string definition for message of type 'Object"
  (cl:format cl:nil "int32 object_index~%float32 confidence # A value between 0.0 and 1.0.~%Rect bounding_box_cv # A bounding box on the camera coordinate.~%geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.~%uint8 label~%uint8 LABEL_UNKNOWN=0~%uint8 LABEL_PEDESTRIAN=1~%uint8 LABEL_CONE=2~%uint8 LABEL_GOLF=3~%uint8 LABEL_SPRINKLER=4~%~%================================================================================~%MSG: am_msgs/Rect~%float32 x~%float32 y~%float32 width~%float32 height~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Object>))
  (cl:+ 0
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bounding_box_cv))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'location_bv) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Object>))
  "Converts a ROS message object to a list"
  (cl:list 'Object
    (cl:cons ':object_index (object_index msg))
    (cl:cons ':confidence (confidence msg))
    (cl:cons ':bounding_box_cv (bounding_box_cv msg))
    (cl:cons ':location_bv (location_bv msg))
    (cl:cons ':label (label msg))
))
