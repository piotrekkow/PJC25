//#include <vector>
//#include <memory> // For smart pointers
//#include <map>    // Or unordered_map
//#include <string>
//#include <optional> // For optional elements like signals
//#include <iostream>
//
//// Forward Declarations (to handle circular dependencies)
//class Link;
//class Lane;
//class Segment;
//class Intersection;
//class TrafficSignalController; // Assuming a separate class for signals
//
//// --- Basic Geometry ---
//struct Point {
//    double x = 0.0;
//    double y = 0.0;
//    double z = 0.0; // Optional altitude
//};
//
//// --- Lane Definition ---
//class Lane {
//public:
//    int lane_id; // Unique identifier
//    int index_in_segment; // e.g., 0 = rightmost, increasing leftwards
//    double width = 3.5; // meters
//    double speed_limit = 50.0; // km/h (or m/s)
//    // Allowed vehicle types, restrictions (e.g., enum flags)
//    // ... other lane-specific attributes (grade, surface?)
//
//    // Ownership: Lane is owned by Segment. Raw pointer back is safe.
//    Segment* parent_segment = nullptr;
//
//    // Connectivity (optional, useful for lane changes): Raw pointers are okay
//    // as neighbors have the same owner (Segment) and lifetime.
//    Lane* left_neighbor = nullptr;
//    Lane* right_neighbor = nullptr;
//
//    Lane(int id, int index, Segment* parent) : lane_id(id), index_in_segment(index), parent_segment(parent) {}
//    // Methods: getCenterlineGeometry(), canVehicleEnter(), etc.
//};
//
//// --- Link Segment (Lengthwise Division) ---
//class Segment {
//public:
//    int segment_id; // Unique identifier (or relative index within Link)
//    double start_offset_in_link; // Distance from link start
//    double length;
//    std::vector<Point> centerline_geometry; // Shape points for this segment
//
//    // Ownership: Segment owns its Lanes
//    std::vector<std::unique_ptr<Lane>> lanes;
//
//    // Ownership: Segment is owned by Link. Raw pointer back is safe.
//    Link* parent_link = nullptr;
//
//    Segment(int id, double start_offset, double len, Link* parent)
//        : segment_id(id), start_offset_in_link(start_offset), length(len), parent_link(parent) {
//    }
//
//    void addLane() {
//        int new_lane_id = generate_unique_lane_id(); // Placeholder
//        int index = static_cast<int>(lanes.size());
//        lanes.push_back(std::make_unique<Lane>(new_lane_id, index, this));
//        // Update neighbor pointers if necessary
//        if (index > 0) {
//            lanes[index]->right_neighbor = lanes[index - 1].get();
//            lanes[index - 1]->left_neighbor = lanes[index].get();
//        }
//    }
//
//    Lane* getLaneByIndex(int index) {
//        if (index >= 0 && index < lanes.size()) {
//            return lanes[index].get();
//        }
//        return nullptr;
//    }
//    // Methods: getNumLanes(), calculateSegmentGeometry(), etc.
//
//private:
//    int generate_unique_lane_id() { /* ... implementation ... */ static int next_id = 0; return ++next_id; }
//};
//
//
//// --- Link (Connection between Intersections) ---
//class Link {
//public:
//    int link_id; // Unique identifier
//
//    // Connectivity: Raw pointers are okay if Intersections outlive Links
//    // (which they typically do if owned by the RoadNetwork).
//    Intersection* start_intersection = nullptr;
//    Intersection* end_intersection = nullptr;
//
//    // Ownership: Link owns its Segments
//    std::vector<std::unique_ptr<Segment>> segments;
//
//    Link(int id, Intersection* start, Intersection* end) : link_id(id), start_intersection(start), end_intersection(end) {}
//
//    void addSegment(double length, const std::vector<Point>& geometry = {}) {
//        int new_segment_id = generate_unique_segment_id(); // Placeholder
//        double start_offset = 0.0;
//        if (!segments.empty()) {
//            start_offset = segments.back()->start_offset_in_link + segments.back()->length;
//        }
//        auto segment = std::make_unique<Segment>(new_segment_id, start_offset, length, this);
//        segment->centerline_geometry = geometry; // Add shape points
//        segments.push_back(std::move(segment));
//    }
//
//    double getTotalLength() const {
//        double total_length = 0;
//        for (const auto& seg : segments) {
//            total_length += seg->length;
//        }
//        return total_length;
//    }
//
//    // Methods: getSegmentAtDistance(dist), getStartIntersection(), getEndIntersection()
//
//private:
//    int generate_unique_segment_id() { /* ... implementation ... */ static int next_id = 0; return ++next_id; }
//};
//
//// --- Intersection Connection Logic ---
//class Connection {
//public:
//    int connection_id;
//    // Connectivity: Raw pointers to lanes involved. Lifetimes managed by Segment.
//    Lane* from_lane = nullptr;
//    Lane* to_lane = nullptr;
//    // Type (left, straight, right), priority rules, geometry within intersection
//    // Optional link to signal phase
//    int signal_group_id = -1; // ID linking to a signal phase/group
//
//    Connection(int id, Lane* from, Lane* to) : connection_id(id), from_lane(from), to_lane(to) {}
//};
//
//// --- Intersection (Node in the Graph) ---
//class Intersection {
//public:
//    int intersection_id; // Unique identifier
//    Point position;
//
//    // Connectivity: Store raw pointers to connected Links. Lifetime managed by RoadNetwork.
//    std::vector<Link*> incoming_links;
//    std::vector<Link*> outgoing_links;
//
//    // Ownership: Intersection owns its internal Connections
//    std::vector<std::unique_ptr<Connection>> connections;
//
//    // Optional Signal Controller (using shared_ptr if controller might be shared or managed separately)
//    std::shared_ptr<TrafficSignalController> signal_controller;
//    // Or priority rules data for unsignalized intersections
//
//    Intersection(int id, Point pos) : intersection_id(id), position(pos) {}
//
//    void addConnection(Lane* from, Lane* to) {
//        int new_conn_id = generate_unique_connection_id(); // Placeholder
//        connections.push_back(std::make_unique<Connection>(new_conn_id, from, to));
//    }
//
//    // Methods: getConnections(from_lane), updateSignalState(time), isSignalized()
//
//private:
//    int generate_unique_connection_id() { /* ... implementation ... */ static int next_id = 0; return ++next_id; }
//};
//
//// --- Road Network Container ---
//class RoadNetwork {
//public:
//    // Ownership: RoadNetwork owns all Intersections and Links
//    std::map<int, std::unique_ptr<Intersection>> intersections;
//    std::map<int, std::unique_ptr<Link>> links;
//    // Could also own signal controllers if not managed externally
//
//    Intersection* addIntersection(int id, Point pos) {
//        auto result = intersections.emplace(id, std::make_unique<Intersection>(id, pos));
//        if (result.second) { // Check if insertion took place
//            return result.first->second.get();
//        }
//        return nullptr; // Or throw error if ID already exists
//    }
//
//    Link* addLink(int id, int start_intersection_id, int end_intersection_id) {
//        Intersection* start_node = getIntersection(start_intersection_id);
//        Intersection* end_node = getIntersection(end_intersection_id);
//
//        if (!start_node || !end_node) {
//            // Handle error: Intersection not found
//            return nullptr;
//        }
//
//        auto result = links.emplace(id, std::make_unique<Link>(id, start_node, end_node));
//        if (result.second) {
//            Link* new_link = result.first->second.get();
//            start_node->outgoing_links.push_back(new_link);
//            end_node->incoming_links.push_back(new_link);
//            return new_link;
//        }
//        return nullptr; // Or throw error if ID already exists
//    }
//
//    Intersection* getIntersection(int id) {
//        auto it = intersections.find(id);
//        return (it != intersections.end()) ? it->second.get() : nullptr;
//    }
//
//    Link* getLink(int id) {
//        auto it = links.find(id);
//        return (it != links.end()) ? it->second.get() : nullptr;
//    }
//
//    // Methods: buildFromData(...), findRoute(...), etc.
//};
//
//int main() {
//    std::cout << "Starting Traffic Simulation Program..." << std::endl;
//
//    // 1. Create an instance of your Road Network
//    RoadNetwork network;
//
//    // 2. Load or build the network data (Example)
//    std::cout << "Building a simple network..." << std::endl;
//    Intersection* node1 = network.addIntersection(1, { 0.0, 0.0 });
//    Intersection* node2 = network.addIntersection(2, { 100.0, 0.0 });
//    Intersection* node3 = network.addIntersection(3, { 100.0, 100.0 });
//
//    // --- Declare link pointers in the higher scope ---
//    Link* link12 = nullptr;
//    Link* link23 = nullptr;
//
//    // --- Create Link 12 ---
//    if (node1 && node2) {
//        // Assign to the pointer declared above
//        link12 = network.addLink(101, node1->intersection_id, node2->intersection_id);
//        if (link12) { // Check if link creation succeeded
//            link12->addSegment(100.0); // Add a 100m segment
//            // Check if segment exists before adding lanes
//            if (!link12->segments.empty()) {
//                link12->segments[0]->addLane(); // Add one lane to the first segment
//                link12->segments[0]->addLane(); // Add a second lane
//                std::cout << "Added Link 101 with 2 lanes." << std::endl;
//            }
//            else {
//                std::cerr << "Warning: Failed to add segment to Link 101." << std::endl;
//            }
//        }
//        else {
//            std::cerr << "Error: Failed to create link 101." << std::endl;
//        }
//    }
//    else {
//        std::cerr << "Error: Could not find node 1 or node 2 to create link 101." << std::endl;
//    }
//
//    // --- Create Link 23 and Connection ---
//    if (node2 && node3) {
//        // Assign to the pointer declared above
//        link23 = network.addLink(102, node2->intersection_id, node3->intersection_id);
//        if (link23) { // Check if link creation succeeded
//            link23->addSegment(100.0);
//            // Check if segment exists before adding lanes/connections
//            if (!link23->segments.empty()) {
//                link23->segments[0]->addLane();
//                std::cout << "Added Link 102 with 1 lane." << std::endl;
//
//                // --- Add connection from link12 to link23 at node2 ---
//                // Crucially, check if link12 was actually created successfully before using it
//                if (link12 && node2) {
//                    // Add checks: Ensure segments and lanes exist before accessing
//                    Lane* fromLane = nullptr;
//                    if (!link12->segments.empty() && link12->segments[0]) {
//                        fromLane = link12->segments[0]->getLaneByIndex(0);
//                    }
//
//                    Lane* toLane = nullptr;
//                    if (!link23->segments.empty() && link23->segments[0]) {
//                        toLane = link23->segments[0]->getLaneByIndex(0);
//                    }
//
//                    // Only add connection if both lanes were found
//                    if (fromLane && toLane) {
//                        node2->addConnection(fromLane, toLane);
//                        std::cout << "Added connection in Intersection 2 (Lane 0 -> Lane 0)." << std::endl;
//                    }
//                    else {
//                        std::cerr << "Error: Could not find required lanes for connection at node 2." << std::endl;
//                        if (!fromLane) std::cerr << "  Reason: fromLane (Link 101, Seg 0, Lane 0) not found.\n";
//                        if (!toLane) std::cerr << "  Reason: toLane (Link 102, Seg 0, Lane 0) not found.\n";
//                    }
//                }
//                else {
//                    std::cerr << "Warning: Cannot create connection at node 2 because link 101 was not successfully created earlier." << std::endl;
//                }
//            }
//            else {
//                std::cerr << "Warning: Failed to add segment to Link 102." << std::endl;
//            }
//        }
//        else {
//            std::cerr << "Error: Failed to create link 102." << std::endl;
//        }
//    }
//    else {
//        std::cerr << "Error: Could not find node 2 or node 3 to create link 102." << std::endl;
//    }
//
//
//    // 3. Initialize simulation components (vehicles, etc.)
//    // ...
//
//    std::cout << "Network setup complete (simulation loop not implemented)." << std::endl;
//    std::cout << "Total intersections: " << network.intersections.size() << std::endl;
//    std::cout << "Total links: " << network.links.size() << std::endl;
//
//
//    // 5. Program ends
//    std::cout << "Exiting Program." << std::endl;
//    return 0; // Indicate successful execution
//}


#include "Simulation.h"

int main()
{
	Simulation simulation;
	
	simulation.initialize();
	simulation.run();
}