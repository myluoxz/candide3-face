//
//  CDFaceData.h
//  candide
//
//  Created by damian on 03/11/13.
//  Copyright (c) 2013 Damian Stewart. All rights reserved.
//

#ifndef __candide__CandideFaceData__
#define __candide__CandideFaceData__

#include <iostream>

#include <string>
#include <map>
#include <vector>

#include "CDMesh.h"

class CDFaceDistortionUnit
{
public:
	CDFaceDistortionUnit( const std::string& name = "" );
	void setName( const std::string& n ) { name = n; }
	std::string getName() const { return name; }
	
	void addVertexOffset( unsigned short vIdx, glm::vec3 offset );
	
	/// apply this shape unit to the target mesh with the given factor (usually 0..1)
	void apply( float amount, CDMesh& target ) const;
	
private:
	
	std::string name;
	std::map<unsigned short, glm::vec3> offsets;
	
	
};


class CDFaceData
{
public:
	/// filename is in wfm format, see candide3
	CDFaceData( const std::string &path );
	
	void draw( const glm::vec3& centerPos, const glm::vec3& fitSize );
	
	std::vector<std::string> getShapeUnitNames();
	void setShapeUnitValue( std::string suName, float value );

	
	void set_maptex_callback(int (*f)()){ maptex_callback=f; };
	int (*maptex_callback)();

	float yaw;

private:
	
	CDMesh getDistortedMesh();
	
	void load( const std::string& path );
	
	/// returns npos if not found
	size_t getIndexOfShapeUnit( const std::string& name );

	// data
	CDMesh meshAtRest;
	std::vector<CDFaceDistortionUnit> shapeUnits;
	std::vector<CDFaceDistortionUnit> animationUnits;
	
	// settings for distortion
	std::map<size_t,float> shapeUnitSettings;
	std::map<size_t,float> animationUnitSettings;;
};


#endif /* defined(__candide__CandideFaceData__) */
