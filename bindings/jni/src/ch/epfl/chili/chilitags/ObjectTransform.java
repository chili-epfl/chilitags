/*******************************************************************************
*   Copyright 2014 EPFL                                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

package ch.epfl.chili.chilitags;

/**
 * Simple wrapper for the Chilitags3D object transform.
 * 
 * @author Ayberk Özgür
 *
 */
public class ObjectTransform{
	/**
	 * The name of this object.
	 */
	public String name;

	/**
	 * The transform 4x4 matrix, relative to the camera frame.
	 */
	public double[][] transform;

	/**
	 * Creates a new ObjectTransform with empty name and identity transform.
	 */
	public ObjectTransform(){
		name = "";
		transform = new double[4][4];
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				transform[i][j] = i == j ? 1 : 0;
	}
}