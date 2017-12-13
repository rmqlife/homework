/*
This file contains class definitions for Vectors and Segments.

It addition
1) Shows you how to use tinyxml to parse XML.  In this case, it reads the
included Menge Scene Specification file and prints summary information about
what it found.
2) Provide a function which computes the minimum distance between two
line segments.

Authors:
	Sean Curtis
	Sahil Narang (minor updates)

*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <math.h>
#include <vector>
#include "tinyxml.h"
#include <time.h>
using namespace std;

#define BIG 1e15
#define SMALL 1e-10
/*!
 *	@brief		Simple 2D vector class.
 */
class Vector2 {
public:
	/*!
	 *	@brief		Constructor.
	 *
	 *	@param		x		The x-value of the vector.
	 *	@param		y		The y-value of the vector.
	 */
	Vector2( float x=0.f, float y=0.f ): _x(x), _y(y) {}
	/*!
	 *	@brief		Vector2 difference.
	 *
	 *	@param		v		The vector to subtract.
	 *	@returns	A vector containing the element-wise difference
	 *				of this vector and v.
	 */
	Vector2 operator-( const Vector2 & v ) const {
		return Vector2( _x - v._x, _y - v._y );
	}

	/*!
	 *	@brief		Vector2 addition.
	 *
	 *	@param		v		The vector to add.
	 *	@returns	A vector containing the element-wise difference
	 *				of this vector and v.
	 */
	Vector2 operator+( const Vector2 & v ) const {
		return Vector2( _x + v._x, _y + v._y );
	}

	/*!
	 *	@brief		Scalar multiplication.
	 *
	 *	@param		s		The scale factor.
	 *	@returns	A vector with each element multiplied by s.
	 */
	Vector2	operator*( float s ) const {
		return Vector2( _x * s, _y * s );
	}

	/*!
	 *	@brief		Short-hand for dot product.std::
	 *
	 *	@param		v		The vector with which the inner product is computed.
	 *	@returns	The inner product (sum of element-wise multiplication)
	 *				of this vector and v.
	 */
	float operator*( const Vector2 & v ) const {
		return _x * v._x + _y * v._y;
	}

	/*!
	 *	@brief		Returns a normalized version of this vector
	 *				(same direction, unit length).
	 *
	 *	If the length of the vector < EPS, then the vector
	 *	<1, 0> is returned.
	 *
	 *	@returns	The normalized vector.
	 */
	Vector2 norm() const {
		float mag = magnitude();
		if ( mag > 0.00001f ) {
			return Vector2( _x / mag, _y / mag );
		} else {
			return Vector2( 1.f, 0.f );
		}
	}

	/*!
	 *	@brief		Returns the magnitude of the vector.
	 *
	 *	@returns	The vector magnitude.
	 */
	inline float magnitude() const { return sqrt( _x * _x + _y * _y ); }

	/*!
	 *	@brief		The x-coordinate of the vector.
	 */
	float	_x;


	/*!
	 *	@brief		The y-coordinate of the vector.
	 */
	float	_y;
};

Vector2 operator*( float s, const Vector2 & v ) {
	return Vector2( s * v._x, s * v._y );
}

/*!
 *	@brief		Compute the "determinant" of two vectors.
 *
 *	It is the determininat of a 2x2 matrix whose columsn are
 *	made up of v1 an v2.
 *
 *	@param		v1		The first column.
 *	@param		v2		The second column.
 *	@returns	The determinant of the 2x2 matrix.
 */
float det( const Vector2 & v1, const Vector2 & v2 ) { 
	return v1._x * v2._y - v1._y * v2._x;
}

/*!
 *	@brief		A line segment.
 */
class Segment {
public:
	/*!
	 *	@brief		Constructor.
	 *
	 *	@param		p0		One end point.
	 *	@param		p1		The other end point.
	 */
	Segment( const Vector2 & p0, const Vector2 & p1 ): _p0(p0), _p1(p1) {}

	/*!
	 *	@brief		Provides the direction from p0 to p1.
	 *
	 *	@returns	A unit-length vector of the direction of the segment form
	 *				p0 to p1.
	 */
	inline Vector2 direction() const { return ( _p1 - _p0 ).norm(); }

	/*!
	 *	@brief		Provides the length fo the segment.
	 *
	 *	@returns	The segment length.
	 */
	inline float length() const { return ( _p1 - _p0 ).magnitude(); }

	/*!
	 *	@brief		Reverses the end point order
	 */
	void flip() {
		Vector2 tmp = _p0;
		_p0 = _p1;
		_p1 = tmp;
	}

	/*!
	 *	@brief		The first end point.
	 */
	Vector2	_p0;

	/*!
	 *	@brief		The first end point.
	 */
	Vector2	_p1;
};

/*!
 *	@brief		Compute the smallest distance between two line segments.
 *
 *	@param		seg1		The first segment.
 *	@param		seg2		The second segmend.
 *	@returns	The distance between the closest features on the two segments.
 */
float minDistance( const Segment & seg1, const Segment & seg2 ) {
	Vector2 qDir = seg1.direction();
	float qLen = seg1.length();
	Vector2 q0 = seg1._p0;
	Vector2 q1 = seg1._p1;

	float pLen = seg2.length();
	Vector2 pDir = seg2.direction();
	Vector2 p0 = seg2._p0;
	Vector2 p1 = seg2._p1;

	if ( fabs( qDir * pDir ) >= 0.9999f ) {
		/// The two segments lie on parallel lines
		///	If one projects onto the other at all, then it is the distance between the lines
		///	otherwise, the distance between the closest end points.

		// Project p0 and p1 onto the line segment
		float t0 = qDir * ( p0 - q0 );
		float t1 = qDir * ( p1 - q0 );
		if ( t0 > qLen && t1 > qLen ) {
			// seg2 is beyond seg 1's second end point-30
			if ( t0 < t1 ) {	// p0 is closest to q1
				return ( p0 - q1 ).magnitude();
			} else {			// p1 is closest to q1
				return ( p1 - q1 ).magnitude();
			}
		} else if ( t0 < 0.f && t1 < 0.f ) {
			// seg2 is before seg 1's first end point
			if ( t0 > t1 ) {	// p0 is closest to q0
				return ( p0 - q0 ).magnitude();
			} else {			// p1 is closest to q0
				return ( p1 - q0 ).magnitude();
			}
		} else {
			// There is overlap - distance is distance between lines
			Vector2 test = q0 + qDir * t0;
			return ( test - p0 ).magnitude();
		}
	} else {
		/// Test for intersection

		// Where do the lines intersect
		float denom = det( qDir, pDir ); 
		float num = det( pDir, q0 - p0 );
		if ( fabs( denom ) <= 0.0001f ) {
			float altNum = det( pDir, q1 - p0 );
			if ( ( altNum >= 0.f && num <= 0.f ) ||
				( altNum <= 0.f && num >= 0.f ) ) {
				// The two end points of q lie onObstacle opposite sides of q
				return 0.f;
			}
		} else {
			// Lines converge
			//float t = num / denom;
			//if ( t >= 0.f && t <= qLen ) {
			//	Vector2 s = q0 + qDir * t;
			//	if ( ( s - p0 ) * pDir <= pLen ) {
			//		// lines intersect in the segment intervals
			//		return 0.f;
			//	}
			//}
			/*New code using https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect*/
			// Consider the intersection point on <p0,p1>
			float u = det((p0 - q0), pDir) / (det(qDir, pDir)); //Essentially intesection pt is q0 + u*qDir
			// Consider the intersection point on <q0,q1>
			float t = det((q0 - p0), qDir) / (det(pDir, qDir));  //Essentially intesection pt is p0 + t*pDir
			if (t <= pLen && t > 0) {
				if (u <= qLen && u > 0) {
					// lines intersect in the segment intervals
					return 0.f;
				}
			}


		}
			
		/// first test the distances between segment end points
		float closestDist = ( p0 - q0 ).magnitude();

		float dist = ( p1 - q0).magnitude();
		closestDist = dist < closestDist ? dist : closestDist;
		dist = ( p0 - q1 ).magnitude();
		closestDist = dist < closestDist ? dist : closestDist;
		dist = ( p1 - q1 ).magnitude();
		closestDist = dist < closestDist ? dist : closestDist;

		// Now test for projections of endpoints onto segments
		Vector2 s;
		float t = qDir * ( p0 - q0 );
		if ( t >= 0 && t <= qLen ) {
			s = q0 + t * qDir;
			dist = ( p0 - s ).magnitude();
			closestDist = dist < closestDist ? dist : closestDist;
		}
		t = qDir * ( p1 - q0 );
		if ( t >= 0 && t <= qLen ) {
			s = q0 + t * qDir;
			dist = ( p1 - s ).magnitude();
			closestDist = dist < closestDist ? dist : closestDist;
		}
		t = pDir * ( q0 - p0 );
		if ( t >= 0 && t <= pLen ) {
			s = p0 + t * pDir;
			dist = ( q0 - s ).magnitude();
			closestDist = dist < closestDist ? dist : closestDist;
		}
		t = pDir * ( q1 - p0 );
		if ( t >= 0 && t <= pLen ) {
			s = p0 + t * pDir;
			dist = ( q1 - s ).magnitude();
			closestDist = dist < closestDist ? dist : closestDist;
		}
		return closestDist;
	}
}

////////////////////////////////////////////////////////////////////

/*!
 *	@brief		Parse an `<Obstacle>` tag.
 *
 *	@param		A pointer to the Obstacle node.
 *	@returns	True if parsing is successful, false otherwise.
 */
 
class Obstacle{
public:
    vector<Segment> segments;
    vector<Vector2> vertices;
    bool closed;
    bool get_segments(){
    	for (int i=0; i<vertices.size(); ++i){
	        int j=i+1;
	        if (i==vertices.size()-1)
	            if (closed)
	                j=0;
	            else
	                break;
	        Segment s(vertices[i],vertices[j]);
	        segments.push_back(s);
	    }
    }
    
    Segment rotate_round(Vector2 p, float angle, float r){
    float x = p._x + r*cos( angle );
    float y = p._y + r*sin( angle );
    return Segment(p, Vector2(x,y));
    }
    
    void print_vec2(Vector2 v) {
        cout<<'('<<v._x<<", "<<v._y<<')';  
    }

    void print_segment(Segment s) {
        cout<<'[';
        print_vec2(s._p0);
        print_vec2(s._p1);
        cout<<']';
    }
    float minDist(Segment s1){
        float min = BIG;
        for (int j = 0; j<segments.size(); j++){
            float d = minDistance(s1,segments[j]);
            if (d<min)
                min = d;
        }
        return min;
    }
    

    
        
    bool point_in(Vector2 p){
    	const float PI = 3.1415975f;
	    const float RAD_TO_DEG = 180.f / PI;
	    const int SAMPLES = 4;
	    const float D_THETA = 2.f * PI / SAMPLES;
    	float angle=0;
        // every direction should have at least one intersection
        for ( int i = 0; i < SAMPLES; ++i ) {
            bool intersect = false;
            Segment s1 = rotate_round(p, angle, 1000);
            float d = minDist(s1);
            // no intersect for this direction, then out of the obstacle
            if (d>SMALL)
                return false;
            angle += D_THETA;
		}
		// have intersection with each obstacle
		return true;    
	}
    
    bool point_near(Vector2 p, float radius){
        Segment s(p,p);
        return minDist(s)<radius;
    }
};


bool parseObstacle( TiXmlElement * node, Obstacle &ob) {
	int iVal;
	// First parse the attributes: bounding box, closed and class
	//bool isBoundBox = false;
	//if ( node->Attribute( "boundingbox", &iVal ) ) {
	//	isBoundBox = (iVal != 0);
	//}

	ob.closed = false;
	if ( node->Attribute( "closed", &iVal ) ) {
		ob.closed = (iVal != 0);
	}

	size_t classID = 1;
	if ( node->Attribute( "class", &iVal ) ) {
		classID = (size_t)iVal;
	}

	// Now parse vertices
	double dVal;

	bool valid = true;
	
	for ( TiXmlElement * vert = node->FirstChildElement(); vert; vert = vert->NextSiblingElement() ) {
		if ( vert->ValueStr() == "Vertex") {
			float p_x = 0;
			float p_y = 0;
			if ( vert->Attribute( "p_x", &dVal) ) {
				p_x = (float)dVal;
			} else {
				valid = false;
			}
			if ( vert->Attribute( "p_y", &dVal) ) {
				p_y = (float)dVal;
			} else {
				valid = false;
			}

			if ( ! valid ) {
				std::cerr << "Missing full x-/y- values in Obstacle Vertex!" << std::endl;
				return false;
			}
			ob.vertices.push_back( Vector2( p_x, p_y ) );
		} else {
			valid = false;
		}
		if ( ! valid ) {
			std::cerr << "Missing attributes in Obstacle!" << std::endl;
			return false;
		}
	}
    ob.get_segments();
	return 1;
}




/*!
 *	@brief		Parse the xml file1.333 -5.333
5.333 -5.333
5.333 -1.333
1.333 -1.333

 *	A simple example that shows how to use tiny xml to parse the xml file.
 *
 *	@param		xmlName		The name of the xml file to parse.
 *	@returns	True if parsing was successful, false otherwise.
 */
 
 
bool parseXML(const std::string & xmlName, vector<Obstacle> &obset) {
	std::cout << "Loading from xml: " << xmlName << "\n";
	TiXmlDocument xml( xmlName );
	bool loadOkay = xml.LoadFile();

	// Make sure that the xml was well-formed
	if ( !loadOkay ) {	// load xml file748070
		std::cerr << "Could not load simulation xml " << xmlName << ".\n";
		return false;
	}

	TiXmlElement* experimentNode = xml.RootElement();	
	if( ! experimentNode ) {
		std::cerr << "Root element does not exist.\n";
		return false;
	}

	// Make sure the root tag is what you expect
	if( experimentNode->ValueStr () != "Experiment" ) {
		std::cerr << "Root element value is not 'Experiment'.\n";
		return false;
	}
    

	// Now parse the child tags of the expermient node
	TiXmlElement* child;
	TiXmlElement* grandChild;
	for( child = experimentNode->FirstChildElement(); child; child = child->NextSiblingElement()) {
		//std::cout<<"Found tag: " << child->ValueStr() << "\n";
		if (child->ValueStr() == "ObstacleSet") {// Parse obstacle sets
			for (grandChild = child->FirstChildElement(); grandChild; grandChild = grandChild->NextSiblingElement())
			{
				if (grandChild->ValueStr() == "Obstacle") {
				    Obstacle ob;
					parseObstacle(grandChild, ob);
					obset.push_back(ob);
				}
				else {
					// You can ignore unexpected tags or report a problem.  In this case, we'll report a problem
					std::cerr << "Encountered an unexpected tag: " << grandChild->ValueStr() << "\n";
					return false;
				}
			}
		}
	}
	
	return true;
}

/*!
 *	@brief		Rotates tinhe segment around the origin by the given amount.
 *
 *	@param		seg			The segment to rotate.
 *	@param		angle		The rotation amount (in radians).
 *	@returns	The rotated segment.
 */



Vector2 get_v(const Vector2 &min_vertex, const Vector2 &max_vertex, vector<Obstacle> &obset, float radius){
    while(true){
        double x_range = max_vertex._x - min_vertex._x;
	    double y_range = max_vertex._y - min_vertex._y;
	    double rand_x = (double)rand()/RAND_MAX * x_range + min_vertex._x;
	    double rand_y = (double)rand()/RAND_MAX * y_range + min_vertex._y;
	    Vector2 p(rand_x,rand_y);
	    bool clear = true;

	    for (int j=0; j<obset.size(); ++j)
	        if (obset[j].point_in(p)){
	            clear=false;
	            break;
	        }
	    
	    for (int j=0; j<obset.size(); ++j)
	        if (obset[j].point_near(p, radius)){
	            clear=false;
	            break;
	        }
	    

	    if (clear){
   	        return p;
        }
    }
    return Vector2(0,0);
}



float distance_vector2(Vector2 p, Vector2 p1)
{
    return minDistance(Segment(p,p), Segment(p1,p1));
}

void k_nearest(Vector2 p, vector<Vector2> &vset, int k, vector<int> &ret){

    vector<bool> fag(vset.size());
    vector<float> dist(vset.size());
    for (int i=0; i<fag.size(); i++){
        fag[i]=0;
    }
    
    for (int i=0; i<vset.size(); i++){
        dist[i] = distance_vector2(vset[i],p);
    }
    

    int min_i = 0;
    
    for (int j=0; j<k; j++){
        float min = BIG;
        
        for (int i=0; i<vset.size(); i++){
            if (dist[i]>SMALL && dist[i]<min && fag[i]==0) {// a valid candidate
                min = dist[i];
                min_i = i;
            }
        }
        fag[min_i] = 1;
        ret.push_back(min_i);
    }
    
    return;
}


int main() {
	cout << "Parsing xml file\n";
	vector<Obstacle> obset;
	//parseXML( "testSceneFile.xml",obset);
    parseXML( "/home/rmqlife/work/homework/comp790-58/hw1/Exe/bottleneck/bottleneckS.xml",obset);
	srand(time(NULL));
	// generate a random point in a area
    Vector2 min_v(-30,-15);
    Vector2 max_v(30, 15);
    const double radius = 0.1;
    const int k_value = 3;
    vector<Vector2> vset;
    Obstacle util;
    for (int i=0; i<15000; ++i){
	    Vector2 v = get_v(min_v,max_v,obset,radius);
	    vset.push_back(v);
    }

    vector<Vector2> eset;
    for (int i=0; i<vset.size(); i++){
        vector<int> k_list;
        k_nearest(vset[i], vset, k_value, k_list);
        for (int j=0; j<k_list.size(); j++){
            //probable
            Vector2 e(i,k_list[j]);
            bool add_fag = 1;
            //compare with the eset
            for (int k=0; k<eset.size(); k++)
                if ((eset[k]._y==e._x && eset[k]._x==e._y)
                  ||(eset[k]._x==e._x && eset[k]._y==e._y)){
                    add_fag = 0;
                    break;
                }

            if (add_fag)
                eset.push_back(e);
            }

        }


//	    for (int j=0; j<k_list.size(); j++){
//	        if (ccmap[i][k_list[j]]==0 && ccmap[k_list[j]][i]==0){
//	            ccmap[i][k_list[j]] = 1;
//	            ccmap[k_list[j]][i] = 1;
//	            Vector2 e(i,k_list[j]);
//	            eset.push_back(e);
//	        }
//	    }
//	}
    // output result:
    ofstream fout;
    fout.open("/home/rmqlife/work/homework/comp790-58/hw1/Exe/bottleneck/roadmap.txt");
    fout<<vset.size()<<endl;
    cout<<"vertex set size: "<<vset.size()<<endl;
    for (int i=0; i<vset.size(); i++){
        fout<<vset[i]._x<<" "<<vset[i]._y<<endl;
    }
    fout<<eset.size()<<endl;
    cout<<"edge set size: "<<eset.size()<<endl;
	for (int i=0; i<eset.size(); i++){
        fout<<eset[i]._x<<" "<<eset[i]._y<<endl;
    }
    fout.close();
	return 0;
}
