int32 object_index
float32 confidence # A value between 0.0 and 1.0.
Rect bounding_box_cv # A bounding box on the camera coordinate.
geometry_msgs/Point[] location_bv # A location on the bird-view coordinate. Z component is always 0.
uint8 label
uint8 LABEL_UNKNOWN=0
uint8 LABEL_PEDESTRIAN=1
uint8 LABEL_CONE=2
uint8 LABEL_GOLF=3
uint8 LABEL_SPRINKLER=4
