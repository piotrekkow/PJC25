#include "Road.h"


#pragma once
class Network
{
	/** Owns roads */
	std::vector<std::unique_ptr<Road>> m_roads;

	bool hasMerge{ false };

public:
	/**
	 * @brief Adds a road
	 * Creates two nodes and a segment connecting them
	 * @param sourcePos Position of the source node
	 * @param destinationPos Position of the destination node
	 * @param size Number of lanes (vertices both nodes)
	 * @return Raw road pointer
	 */
	Road* addRoad(Vector2 sourcePos, Vector2 destinationPos, int size);
	
	// ?? Should connectRoad be here or lower down?

	/**
	* @brief Connects two existing roads. The newly created segment is owned by the road which owns the source node.
	* @details
	* given:
	* [] : vertex (array of these is a node)  
	* -- : edge (array of these is a segment)  
	* 
	* examples:
	* 2[]---[]1  
	* 1[]---[]0  
	* 0[]	
	* src	dst
	* srcOffset=1, dstOffset=0, laneCount=2
	* 
	* 2[]
	* 1[]---[]1
	* 0[]---[]0	
	* src	dst
	* srcOffset=0, dstOffset=0, laneCount=2
	* 
	* 2[]---[]2
	* 1[]---[]1
	* 0[]	[]0
	* src	dst
	* srcOffset=1, dstOffset=1, laneCount=2
	* 
	* @param source Source node
	* @param destination Destination node
	* @param srcOffset source offset (starting from 0, has to be less than or equal source.size - laneCount)
	* @param dstOffset destination offset (starting from 0, has to be less than or equal destination.size - laneCount)
	* @param laneCount How many lanes to connect (as a Segment)
	*/
	void connectRoad(Road* sourceRoad, Road* destinationRoad, int srcOffset = 0, int dstOffset = 0, std::optional<int> laneCount = std::nullopt);
	
	auto getRoads() const
	{
		return pointerView(m_roads);
	}
};

