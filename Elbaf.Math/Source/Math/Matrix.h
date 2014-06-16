#pragma once
#include <glm\glm.hpp>
#include "Vector.h"
#include <glm\gtc\matrix_access.inl>

// todo: typedef others (2x4, 2x3 etc)
typedef glm::mat2 Matrix2x2;
typedef glm::mat3 Matrix3x3;
typedef glm::mat4 Matrix4x4;

namespace Matrix
{
	Matrix4x4 CreateLookAt(Vector3f eye, Vector3f target, Vector3f up);
	// CreatePerspective, CreateOrthogonal, Translate, Scale, Rotate etc etc
}

template<typename T, glm::precision P>
std::ostream & operator << (std::ostream & stream, glm::detail::tmat3x3<T, P> const & mat)
{
	stream << "<Matrix3x3>" << std::endl;
	stream << "<row ";
	stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
	stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
	stream << "z=\"" << glm::row(mat, 0)[2] << "\" ";
	stream << "/>" << std::endl;
	stream << "<row ";
	stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
	stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
	stream << "z=\"" << glm::row(mat, 1)[2] << "\" ";
	stream << "/>" << std::endl;
	stream << "<row ";
	stream << "x=\"" << glm::row(mat, 2)[0] << "\" ";
	stream << "y=\"" << glm::row(mat, 2)[1] << "\" ";
	stream << "z=\"" << glm::row(mat, 2)[2] << "\" ";
	stream << "/>" << std::endl;
	stream << "</Matrix3x3>";

	return stream;
}

template<typename T, glm::precision P>
std::ostream & operator << (std::ostream & stream, glm::detail::tmat4x4<T, P> const & mat)
{
	stream << "<Matrix4x4>" << std::endl;
	stream << "<row ";
	stream << "x=\"" << glm::row(mat, 0)[0] << "\" ";
	stream << "y=\"" << glm::row(mat, 0)[1] << "\" ";
	stream << "z=\"" << glm::row(mat, 0)[2] << "\" ";
	stream << "w=\"" << glm::row(mat, 0)[3] << "\" ";
	stream << "/>" << std::endl;
	stream << "<row ";
	stream << "x=\"" << glm::row(mat, 1)[0] << "\" ";
	stream << "y=\"" << glm::row(mat, 1)[1] << "\" ";
	stream << "z=\"" << glm::row(mat, 1)[2] << "\" ";
	stream << "w=\"" << glm::row(mat, 1)[3] << "\" ";
	stream << "/>" << std::endl;
	stream << "<row ";
	stream << "x=\"" << glm::row(mat, 2)[0] << "\" ";
	stream << "y=\"" << glm::row(mat, 2)[1] << "\" ";
	stream << "z=\"" << glm::row(mat, 2)[2] << "\" ";
	stream << "w=\"" << glm::row(mat, 2)[3] << "\" ";
	stream << "/>" << std::endl;
	stream << "<row ";
	stream << "x=\"" << glm::row(mat, 3)[0] << "\" ";
	stream << "y=\"" << glm::row(mat, 3)[1] << "\" ";
	stream << "z=\"" << glm::row(mat, 3)[2] << "\" ";
	stream << "w=\"" << glm::row(mat, 3)[3] << "\" ";
	stream << "/>" << std::endl;
	stream << "</Matrix4x4>";

	return stream;
}