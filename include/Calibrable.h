#pragma once

namespace calidad {

class Calibrable {
public:
    virtual bool calibrar() = 0;
    virtual ~Calibrable() = default;
};

}  // namespace calidad
