#ifndef TACO_FORMAT_H
#define TACO_FORMAT_H

#include <string>
#include <memory>
#include <vector>
#include <ostream>

namespace taco {
class Level;

enum LevelType {
  Dense,      // e.g. first  dimension in CSR
  Sparse,     // e.g. second dimension in CSR
  Fixed,      // e.g. second dimension in ELL
//  Repeated,   // e.g. second dimension in DIA
//  Replicated  // e.g.  first dimension in COO
};

class Format {
public:
  typedef std::vector<LevelType> LevelTypes;
  typedef std::vector<size_t>    DimensionOrders;

  Format();
  Format(LevelTypes levelTypes, DimensionOrders dimensionOrder);
  Format(LevelTypes levelTypes);

  const std::vector<Level>& getLevels() const {return levels;}

private:
  // The levels of the storage forest described by this format.
  std::vector<Level> levels;
};

std::ostream &operator<<(std::ostream&, const Format&);


class Level {
public:
  Level(size_t dimension, LevelType type) : dimension(dimension), type(type) {}

  LevelType getType() const {
    return type;
  }

  size_t getDimension() const {
    return dimension;
  }

private:
  size_t dimension;  // The tensor dimension described by the format level
  LevelType type;
};

std::ostream& operator<<(std::ostream&, const LevelType&);
std::ostream& operator<<(std::ostream&, const Level&);

}
#endif
