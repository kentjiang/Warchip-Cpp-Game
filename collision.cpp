

bool isCollision(const SDL_Rect &A, const SDL_Rect &B)
{
  bool intersectVertical = false;
  bool intersectHorizontal = false;
  int wideLeft, wideRight, narrowLeft, narrowRight;
  int highTop, highBottom, shortTop, shortBottom;

  if(A.w < B.w)
    {
      wideLeft = B.x;
      wideRight = B.x+B.w;
      narrowLeft = A.x;
      narrowRight = A.x+A.w;
    }
  else
    {
      wideLeft = A.x;
      wideRight= A.x+A.w;
      narrowLeft = B.x;
      narrowRight = B.x+B.w;
    }

  if(A.h < B.h)
    {
      highTop = B.y;
      highBottom = B.y+B.h;
      shortTop = A.y;
      shortBottom = A.y+A.h;
    }
  else
    {
      highTop = A.y;
      highBottom = A.y+A.h;
      shortTop = B.y;
      shortBottom = B.y+B.h;
    }

  if((wideLeft <= narrowLeft && narrowLeft <= wideRight) ||
     (wideLeft <= narrowRight && narrowRight <= wideRight))
    intersectHorizontal = true;
  
  if((highTop <= shortTop && shortTop <= highBottom) ||
     (highTop <= shortBottom && shortBottom <= highBottom))
     intersectVertical = true;
  return intersectVertical && intersectHorizontal;
}
