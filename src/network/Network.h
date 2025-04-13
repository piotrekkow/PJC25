#include "Road.h"


#pragma once
class Network
{
	/** Owns roads */
	std::vector<std::unique_ptr<Road>> m_roads;

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
	* @brief Connects two existing roads
	* The newly created segment is owned by the road which owns the source node
	* @param source Source node
	* @param destination Destination node
	*/
	void connectRoad(Road* source, Road* destination);
	
	auto getRoads() const
	{
		return pointerView(m_roads);
	}
};

