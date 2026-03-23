#pragma once

#include <array>
#include <cmath>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_int2.hpp>
#include <sstream>

namespace VoidEngine::Math {
	template<typename T>
	struct Rect2 {
		glm::vec<2, T> position = { 0, 0 }, size = { 0, 0 };

		[[nodiscard]] glm::vec<2, T> getEndPosition() const {
			return position + size;
		}

		[[nodiscard]] operator std::string() const {
			std::stringstream stream;
			stream << "( { x: " << position.x << " y: " << position.y << " }" <<
				", { w: " << size.x << " h: " << size.y << " })";
			return stream.str();
		}

		[[nodiscard]] bool operator==(const Rect2<T>& RHS) const {
			return position == RHS.position && size == RHS.size;
		}

		[[nodiscard]] bool collidesWith(const Rect2<T>& other) const {
			return position.x <= other.position.x + other.size.x &&
				position.x + size.x >= other.position.x &&
				position.y <= other.position.y + other.size.y &&
				position.y + size.y >= other.position.y;
		}

		[[nodiscard]] bool containsPoint(const glm::vec<2, T>& point) const {
			return point.x >= position.x &&
				point.x <= position.x + size.x &&
				point.y >= position.y &&
				point.y <= position.y + size.y;
		}

		[[nodiscard]] glm::vec2 getCenter() const {
			return position + (size / (T) 2);
		}

		[[nodiscard]] T getVerticalCenter() const {
			return position.y + (size.y / (T) 2);
		}

		[[nodiscard]] T getHorizontalCenter() const {
			return position.x + (size.x / (T) 2);
		}

		[[nodiscard]] std::array<glm::vec<2, T>, 4> getRectVertices() const {
			return {
				glm::vec2 { position.x, position.y },
				{ position.x, position.y + size.y },
				{ position.x + size.x, position.y },
				{ position.x + size.x, position.y + size.y }
			};
		}

		[[nodiscard]] std::array<Rect2<T>, 2> splitHorizontally(T point) const {
			if(point <= position.y || point >= position.y + size.y) {
				return { { position, size } };
			}

			Rect2<T> top = {
				position,
				{ size.x, point - position.y }
			};
			Rect2<T> bottom = {
				{ position.x, position.y + point },
				{ size.x, size.y - (point - position.y) }
			};

			return { top, bottom };
		}

		[[nodiscard]] std::array<Rect2<T>, 2> splitVertically(T point) const {
			if(point <= position.x || point >= position.x + size.x) {
				return { { position, size } };
			}

			Rect2<T> left = {
				position,
				{ point - position.x, size.y }
			};
			Rect2<T> right = {
				{ point, position.y },
				{ size.x - (point - position.x), size.y }
			};

			return { left, right };
		}

		template<typename R>
		[[nodiscard]] Rect2<R> round() const {
			return {
				{ std::round(position.x), std::round(position.y) },
				{ std::round(size.x), std::round(size.y) }
			};
		}

		template<typename R>
		[[nodiscard]] Rect2<R> floor() const {
			return {
				{ std::floor(position.x), std::floor(position.y) },
				{ std::floor(size.x), std::floor(size.y) }
			};
		}

		template<typename R>
		[[nodiscard]] Rect2<R> ceil() const {
			return {
				{ std::ceil(position.x), std::ceil(position.y) },
				{ std::ceil(size.x), std::ceil(size.y) }
			};
		}
	};

	typedef Rect2<float> Rect2f;
	typedef Rect2<double> Rect2d;
	typedef Rect2<int> Rect2i;
}

