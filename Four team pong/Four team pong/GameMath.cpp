#include "GameMath.h"

D2D1_VECTOR_2F GameMath::findInterceptPoint(D2D1_VECTOR_2F linePos, D2D1_VECTOR_2F lineDirUnit, D2D1_VECTOR_2F pos, D2D1_VECTOR_2F vel)
{
    D2D1_VECTOR_2F alphaVect = D2D1::Vector2F(linePos.x - pos.x, linePos.y - pos.y);
    return D2D1::Vector2F(0.0f, 0.0f);
}
