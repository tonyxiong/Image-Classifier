# Image-Classifier
Clusters and positions databases of images with respect to their visual similarity.

### Features
* Clustering of large database of images (**K-means** & **GMM** supported)
* Classification of new images with **Random Forest** classifier
* Positioning of images within each cluster via layout algorithms (tree layout)
* Bag-of-words model for quick comparison of local features

#### Available Image Features:
* Colour Histograms
* Local Features supported by OpenCV (SIFT, SURF, etc..)

#### Dependencies
* OpenCV 2.4.9+
* Qt 5.3
* Open Graph Drawing Framework

#### Screenshots
Histogram Clustering             |  Local Descriptor(SURF) Clustering
:-------------------------:|:-------------------------:
![Clusters formed with colour histogram](http://puu.sh/hy2SD/ae824edde5.jpg)  |  ![Cluster formed with SURF descriptors](http://puu.sh/hxKWM/f2b26b1ead.jpg)

Browsing Inside A Cluster|
--------------------------|
<img src="http://puu.sh/hyW0V/f15b237309.jpg">|
