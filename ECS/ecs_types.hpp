using ComponentType = unsigned int;
const unsigned N_COMPOENT_TYPES = 32;

enum class Component
{Position = 0,SpriteSheet,State,Movable,Controller,Collidable};

enum class System
{Renderer = 0,Movement,Collision,Control,State,SheetAnimation};
