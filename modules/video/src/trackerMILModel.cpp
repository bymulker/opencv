#include "trackerMILModel.hpp"
/**
 * TrackerMILModel
 */

namespace cv
{

TrackerMILModel::TrackerMILModel()
{
	currentSample.clear();
	mode = MODE_POSITIVE;
}

void TrackerMILModel:: modelEstimationImpl( const std::vector<Mat>& responses )
{
	if( currentSample.size() == 0)
	{
		CV_Error(-1, "The samples in Model estimation are empty");
		return;
	}


	for( size_t i = 0; i <  responses.size(); i++ )
	{
		//for each column (one sample) there are #num_feature
		//get informations from currentSample
		for( int j = 0; j < responses.at(i).cols; j++)
		{

			Size currentSize;
			Point currentOfs;
			currentSample.at(j).locateROI( currentSize, currentOfs );
			bool foreground;
			if( mode == MODE_POSITIVE )
			{
				foreground = true;
			}
			else
			{
				foreground = false;
			}

			//get the column of the HAAR responses
			Mat singleResponse = responses.at(i).col(j);

			//create the state
			Ptr<TrackerMILTargetState> currentState = new TrackerMILTargetState( currentOfs,
					currentSize.width,
					currentSize.height,
					foreground,
					singleResponse);

			currentConfidenceMap.push_back( std::make_pair(currentState, 0) );

		}


	}

}

void TrackerMILModel::modelUpdateImpl()
{

}

void TrackerMILModel::setMode( int trainingMode, const std::vector<Mat>& samples )
{
	currentSample.clear();
	currentSample = samples;

	mode = trainingMode;
}

}
