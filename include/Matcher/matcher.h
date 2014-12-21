/** @file matcher.h
 *
 * \brief The core of matching Visual Odometry
 * \author Michal Nowicki
 *
 */

#ifndef _MATCHER_H_
#define _MATCHER_H_

#include "../Defs/putslam_defs.h"
#include <string>
#include <vector>
#include "opencv/cv.h"

namespace putslam {
/// Grabber interface
class Matcher {
public:

	/// Overloaded constructor
	Matcher(const std::string _name) :
			name(_name), frame_id(0) {
	}

	/// Name of the Matcher
	virtual const std::string& getName() const = 0;

//
//            /// Returns the current set of features
//            virtual const ImageFeature::Seq& getFeatures(void) const = 0;
//
//            /// Reset tracking and find new set of features
//            virtual void reset() = 0;
//

	/// Load features at the start of the sequence
	void loadInitFeatures(const SensorFrame& next_frame);

	/// Run single match
	bool match(const SensorFrame& next_frame);

//
//            /// Compute homogenous transformation
//            virtual const RobotPose& computeTransform(void) = 0;
//
//            /// get Vertex: set of Keypoints/ point Cloud and sensor/robot pose
//            virtual const VertexSE3& getVertex(void) = 0;
//
//            /// Virtual descrutor
//            virtual ~Tracker() {}

protected:

	/// Matcher name
	const std::string name;

	/// Frame id
	uint_fast32_t frame_id;

	/// Information about previous keypoints + descriptors
	std::vector<cv::KeyPoint> prevFeatures;
	cv::Mat prevDescriptors;
	std::vector<Eigen::Vector3f> prevFeatures3D;
	cv::Mat prevRgbImage, prevDepthImage;

	// Methods used to visualize results/data
	void showFeatures(cv::Mat rgbImage, std::vector<cv::KeyPoint> features);
	void showMatches(cv::Mat prevRgbImage,
			std::vector<cv::KeyPoint> prevFeatures, cv::Mat rgbImage,
			std::vector<cv::KeyPoint> features, std::vector<cv::DMatch> matches);

//
//            /// Computed homogenous transformation
//            RobotPose transformation;
//
//            /// keypoint: robot/sensor pose + point cloud + features
//            VertexSE3 keypoint;

	/// Detect features
	virtual std::vector<cv::KeyPoint> detectFeatures(cv::Mat rgbImage) = 0;

	/// Describe features
	virtual cv::Mat describeFeatures(cv::Mat rgbImage,
			std::vector<cv::KeyPoint> features) = 0;

	/// Perform matching
	virtual std::vector<cv::DMatch> performMatching(cv::Mat prevDescriptors,
			cv::Mat descriptors) = 0;


};
};

#endif // _MATCHER_H_
