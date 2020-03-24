;; Auto-generated. Do not edit!


(when (boundp 'am_msgs::Object)
  (if (not (find-package "AM_MSGS"))
    (make-package "AM_MSGS"))
  (shadow 'Object (find-package "AM_MSGS")))
(unless (find-package "AM_MSGS::OBJECT")
  (make-package "AM_MSGS::OBJECT"))

(in-package "ROS")
;;//! \htmlinclude Object.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(intern "*LABEL_UNKNOWN*" (find-package "AM_MSGS::OBJECT"))
(shadow '*LABEL_UNKNOWN* (find-package "AM_MSGS::OBJECT"))
(defconstant am_msgs::Object::*LABEL_UNKNOWN* 0)
(intern "*LABEL_PEDESTRIAN*" (find-package "AM_MSGS::OBJECT"))
(shadow '*LABEL_PEDESTRIAN* (find-package "AM_MSGS::OBJECT"))
(defconstant am_msgs::Object::*LABEL_PEDESTRIAN* 1)
(intern "*LABEL_CONE*" (find-package "AM_MSGS::OBJECT"))
(shadow '*LABEL_CONE* (find-package "AM_MSGS::OBJECT"))
(defconstant am_msgs::Object::*LABEL_CONE* 2)
(intern "*LABEL_GOLF*" (find-package "AM_MSGS::OBJECT"))
(shadow '*LABEL_GOLF* (find-package "AM_MSGS::OBJECT"))
(defconstant am_msgs::Object::*LABEL_GOLF* 3)
(intern "*LABEL_SPRINKLER*" (find-package "AM_MSGS::OBJECT"))
(shadow '*LABEL_SPRINKLER* (find-package "AM_MSGS::OBJECT"))
(defconstant am_msgs::Object::*LABEL_SPRINKLER* 4)
(defclass am_msgs::Object
  :super ros::object
  :slots (_object_index _confidence _bounding_box_cv _location_bv _label ))

(defmethod am_msgs::Object
  (:init
   (&key
    ((:object_index __object_index) 0)
    ((:confidence __confidence) 0.0)
    ((:bounding_box_cv __bounding_box_cv) (instance am_msgs::Rect :init))
    ((:location_bv __location_bv) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    ((:label __label) 0)
    )
   (send-super :init)
   (setq _object_index (round __object_index))
   (setq _confidence (float __confidence))
   (setq _bounding_box_cv __bounding_box_cv)
   (setq _location_bv __location_bv)
   (setq _label (round __label))
   self)
  (:object_index
   (&optional __object_index)
   (if __object_index (setq _object_index __object_index)) _object_index)
  (:confidence
   (&optional __confidence)
   (if __confidence (setq _confidence __confidence)) _confidence)
  (:bounding_box_cv
   (&rest __bounding_box_cv)
   (if (keywordp (car __bounding_box_cv))
       (send* _bounding_box_cv __bounding_box_cv)
     (progn
       (if __bounding_box_cv (setq _bounding_box_cv (car __bounding_box_cv)))
       _bounding_box_cv)))
  (:location_bv
   (&rest __location_bv)
   (if (keywordp (car __location_bv))
       (send* _location_bv __location_bv)
     (progn
       (if __location_bv (setq _location_bv (car __location_bv)))
       _location_bv)))
  (:label
   (&optional __label)
   (if __label (setq _label __label)) _label)
  (:serialization-length
   ()
   (+
    ;; int32 _object_index
    4
    ;; float32 _confidence
    4
    ;; am_msgs/Rect _bounding_box_cv
    (send _bounding_box_cv :serialization-length)
    ;; geometry_msgs/Point[] _location_bv
    (apply #'+ (send-all _location_bv :serialization-length)) 4
    ;; uint8 _label
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _object_index
       (write-long _object_index s)
     ;; float32 _confidence
       (sys::poke _confidence (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; am_msgs/Rect _bounding_box_cv
       (send _bounding_box_cv :serialize s)
     ;; geometry_msgs/Point[] _location_bv
     (write-long (length _location_bv) s)
     (dolist (elem _location_bv)
       (send elem :serialize s)
       )
     ;; uint8 _label
       (write-byte _label s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _object_index
     (setq _object_index (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _confidence
     (setq _confidence (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; am_msgs/Rect _bounding_box_cv
     (send _bounding_box_cv :deserialize buf ptr-) (incf ptr- (send _bounding_box_cv :serialization-length))
   ;; geometry_msgs/Point[] _location_bv
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _location_bv (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _location_bv)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; uint8 _label
     (setq _label (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;;
   self)
  )

(setf (get am_msgs::Object :md5sum-) "0c9b334f865e3aab40d33e895236278a")
(setf (get am_msgs::Object :datatype-) "am_msgs/Object")
(setf (get am_msgs::Object :definition-)
      "int32 object_index
float32 confidence # A value between 0.0 and 1.0.
Rect bounding_box_cv # A bounding box on the camera coordinate.
geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.
uint8 label
uint8 LABEL_UNKNOWN=0
uint8 LABEL_PEDESTRIAN=1
uint8 LABEL_CONE=2
uint8 LABEL_GOLF=3
uint8 LABEL_SPRINKLER=4

================================================================================
MSG: am_msgs/Rect
float32 x
float32 y
float32 width
float32 height

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :am_msgs/Object "0c9b334f865e3aab40d33e895236278a")


