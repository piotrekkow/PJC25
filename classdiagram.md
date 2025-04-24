
classDiagram
    class Network {
        std::vector std::unique_ptr Intersection m_intersections
        std::vector std::unique_ptr Link m_links
        +addLink()
        +getLinks()
    }
    class Link {
        std::vector std::unique_ptr Segment m_segments
        
        Intersection* m_startIntersection
        Intersection* m_targetIntersection

        addSegment()
    }
    class Segment {
        std::vector std::unique_ptr Lane m_lanes
        std::unique_ptr Geometry m_geometry
        addLane()
        geometry()
    }
    class Geometry {
        std::vector Point m_points
        Geometry* m_nextSegmentGeometry
        setPoints()
        getPoints()
        removePoint()

        - updatePoints()
    }
    class Point {
        Vector2 coordinates
        Vector2 bisector
        
        move()
        updatePoint()
        - calculateBisector()
    }
    class Lane{
        float m_width
        float m_speedLimit

        getWidth()
    }

    Network *-- Intersection
    Network *-- Link
    Intersection --> Link : outLink
    Intersection --> Link : inLink
    Link *-- "1..n" Segment
    Segment *-- "1" Geometry
    Segment *-- "1..n" Lane

    Geometry --> Geometry : nextSegmentGeometry
    Geometry *-- "1..n" Point

    Intersection *-- Connection
