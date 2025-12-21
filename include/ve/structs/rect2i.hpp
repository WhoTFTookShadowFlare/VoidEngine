#pragma once

#include <array>
#include <glm/ext/vector_int2.hpp>
#include <ostream>
#include <sstream>

namespace VoidEngine::Structs {
	struct Rect2i {
		glm::ivec2 position = { 0, 0 }, size = { 0, 0 };

		glm::ivec2 getEndPosition() const {
			return position + size;
		}

		std::string to_string() const {
			std::stringstream stream;
			stream << "( { x: " << position.x << " y: " << position.y << " }" <<
				", { w: " << size.x << " h: " << size.y << " })";
			return stream.str();
		}

		bool operator==(const Rect2i& RHS) const {
			return position == RHS.position && size == RHS.size;
		}

		bool collidesWith(const Rect2i& other) const {
			return position.x <= other.position.x + other.size.x &&
				position.x + size.x >= other.position.x &&
				position.y <= other.position.y + other.size.y &&
				position.y + size.y >= other.position.y;
		}

		bool containsPoint(const glm::ivec2& point) const {
			return point.x >= position.x &&
				point.x <= position.x + size.x &&
				point.y >= position.y &&
				point.y <= position.y + size.y;
		}

		glm::ivec2 getCenter() const {
			return position + size / 2;
		}

		std::array<glm::ivec2, 4> getRectVertices() const {
			return {
				glm::ivec2 { position.x, position.y },
				{ position.x, position.y + size.y },
				{ position.x + size.x, position.y },
				{ position.x + size.x, position.y + size.y }
			};
		}

		std::array<Rect2i, 2> splitHorizontally(int point) const {
			if(point <= position.y || point >= position.y + size.y) {
				return { { position, size } };
			}

			Rect2i top = {
				position,
				{ size.x, point }
			};
			Rect2i bottom = {
				{ position.x, position.y + point },
				{ size.x, size.y - (point - position.y) }
			};

			return { top, bottom };
		}

		std::array<Rect2i, 2> splitVertically(int point) const {
			if(point <= position.x || point >= position.x + size.x) {
				return { { position, size } };
			}

			Rect2i left = {
				position,
				{ point, size.y}
			};
			Rect2i right = {
				{ point, position.y },
				{ size.x - (point - position.y), size.y }
			};

			return { left, right };
		}
	};
}

