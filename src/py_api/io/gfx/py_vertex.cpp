#include "ve/py_api/io/gfx/py_vertex.hpp"
#include "pocketpy.h"
#include "ve/io/gfx/mesh.hpp"
#include "ve/py_api/math/py_vec3.hpp"
#include "ve/py_api/math/py_vec4.hpp"
#include <format>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>

namespace VoidEngine::PyAPI::IO::GFX {
	using namespace VoidEngine::IO::GFX;

	bool PyVertex__new__(int argc, py_Ref argv);
	bool PyVertex__init__(int argc, py_Ref argv);
	bool PyVertex__repr__(int argc, py_Ref argv);

	bool PyVertex_get_position(int argc, py_Ref argv);
	bool PyVertex_get_color(int argc, py_Ref argv);

	bool PyVertex_set_position(int argc, py_Ref argv);
	bool PyVertex_set_color(int argc, py_Ref argv);

	py_Type vertexType = 0;
	void initVertexPyType(py_GlobalRef module) {
		vertexType = py_newtype("Vertex", tp_object, module, nullptr);
		py_bindmethod(vertexType, "__new__", PyVertex__new__);
		py_bindmethod(vertexType, "__init__", PyVertex__init__);
		py_bindmethod(vertexType, "__repr__", PyVertex__repr__);

		py_bindproperty(vertexType, "position", PyVertex_get_position, PyVertex_get_position);
		py_bindproperty(vertexType, "color", PyVertex_get_color, PyVertex_set_color);
	}

	bool PyVertex__new__(int argc, py_Ref argv) {
		py_Type cls = py_totype(argv);
		py_newobject(py_retval(), cls, 0, sizeof(Vertex));
		return true;
	}

	bool PyVertex__init__(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		Vertex *self = (Vertex*) py_touserdata(py_arg(0));

		self->position = { 0, 0, 0 };
		self->color = { 0, 0, 0, 1 };

		return true;
	}

	bool PyVertex__repr__(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		Vertex *self = (Vertex*) py_touserdata(py_arg(0));
		std::string str = std::format("{{ position: {{ {}, {}, {} }}, color: {{ {}, {}, {}, {} }} }}",
				self->position.x, self->position.y, self->position.z,
				self->color.x, self->color.y, self->color.z, self->color.w
		);
		py_newstr(py_retval(), str.c_str());
		return true;
	}

	bool PyVertex_get_position(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		Vertex *self = (Vertex*) py_touserdata(py_arg(0));
		glm::vec3 *position = (glm::vec3*) py_newobject(py_retval(), Math::vec3Type, 0, sizeof(glm::vec3));
		*position = self->position;
		return true;
	}

	bool PyVertex_get_color(int argc, py_Ref argv) {
		PY_CHECK_ARGC(1);
		Vertex *self = (Vertex*) py_touserdata(py_arg(0));
		glm::vec4 *color = (glm::vec4*) py_newobject(py_retval(), Math::vec4Type, 0, sizeof(glm::vec4));
		*color = self->color;
		return true;
	}

	bool PyVertex_set_position(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		Vertex *self = (Vertex*) py_touserdata(py_arg(0));

		if(!py_isinstance(py_arg(1), Math::vec3Type)) {
			return TypeError("Vertex.position must be of type Vec3");
		}

		glm::vec3 *position = (glm::vec3*) py_touserdata(py_arg(1));
		self->position = *position;

		py_newnone(py_retval());
		return true;
	}

	bool PyVertex_set_color(int argc, py_Ref argv) {
		PY_CHECK_ARGC(2);
		Vertex *self = (Vertex*) py_touserdata(py_arg(0));

		if(!py_isinstance(py_arg(1), Math::vec4Type)) {
			return TypeError("Vertex.color must be of type Vec4");
		}

		glm::vec4 *color = (glm::vec4*) py_touserdata(py_arg(1));
		self->color = *color;

		py_newnone(py_retval());
		return true;
	}
}

