#include "character.hpp"
#include "entity_manager.hpp"

Character::Character(EntityManager* l_entityMgr)
:EntityBase(l_entityMgr),
m_spriteSheet(m_entityManager->GetContext()->m_textureManager),
m_jumpVelocity(250),m_hitpoints(5)
{
    m_name = "Character";
}

void Character::Move(const Direction& l_dir)
{
    if(GetState() == EntityState::Dying) return;

    m_spriteSheet.SetDirection(l_dir);
    if(l_dir == Direction::Left)
    { Accelerate(-m_speed.x,0);}
    else Accelerate(m_speed.x,0);

    if(GetState() == EntityState::Idle)
    { SetState(EntityState::Walking);}
}

void Character::Jump()
{
    if(GetState() == EntityState::Dying||
    GetState() == EntityState::Jumping||
    GetState() == EntityState::Hurt)
    { return; }

    SetState(EntityState::Jumping);
    AddVelocity(0,-m_jumpVelocity);
}

void Character::Attack()
{
    if (GetState() == EntityState::Dying ||
        //GetState() == EntityState::Jumping ||
        GetState() == EntityState::Hurt ||
        GetState() == EntityState::Attacking)
    { return;}
    
	SetState(EntityState::Attacking);
}

void Character::GetHurt(const int& l_damage)
{
    if(GetState() == EntityState::Dying||
    GetState() == EntityState::Hurt)
    { return; }

    m_hitpoints = (m_hitpoints - l_damage > 0 ? m_hitpoints - l_damage : 0);
    if(m_hitpoints) SetState(EntityState::Hurt);
    else SetState(EntityState::Dying);
}

void Character::UpdateAttackAABB()
{
    m_attackAABB.left = 
    (m_spriteSheet.GetDirection() == Direction::Left ?
    (m_AABB.left - m_attackAABB.width) -m_attackAABBoffSet.x
    :(m_AABB.left + m_AABB.width + m_attackAABBoffSet.x));

    m_attackAABB.top = m_AABB.top + m_attackAABBoffSet.y;
}

void Character::Animate()
{
    EntityState state = GetState();
    if(m_spriteSheet.GetCurrentAnim() == nullptr)return;
    if(state == EntityState::Walking && m_spriteSheet.GetCurrentAnim()->GetName() != "Walk")
    {
        // args: name, play, loop
        m_spriteSheet.SetAnimation("Walk",true,true);
    }
    else if(state == EntityState::Jumping && m_spriteSheet.GetCurrentAnim()->GetName() != "Jump")
    {
        m_spriteSheet.SetAnimation("Jump",true,false);
    }
    else if(state == EntityState::Attacking && m_spriteSheet.
    GetCurrentAnim()->GetName() != "Attack")
    {
        m_spriteSheet.SetAnimation("Attack",true,false);
    } 
    else if(state == EntityState::Hurt && m_spriteSheet.
    GetCurrentAnim()->GetName() != "Hurt")
    {
        m_spriteSheet.SetAnimation("Hurt",true,false);
    }
    else if(state == EntityState::Dying && m_spriteSheet.
    GetCurrentAnim()->GetName() != "Death")
    {
        m_spriteSheet.SetAnimation("Death",true,false);
    }
    else if(state == EntityState::Idle && m_spriteSheet.
    GetCurrentAnim()->GetName() != "Idle")
    {
        m_spriteSheet.SetAnimation("Idle",true,true);
    }

}

void Character::Update(float l_dt)
{
    EntityBase::Update(l_dt);
    if(m_attackAABB.width != 0 && m_attackAABB.height != 0)
    {
        UpdateAABB();
    }

    if(GetState()!= EntityState::Dying && 
    GetState()!= EntityState::Attacking &&
    GetState() != EntityState::Hurt)
    {
        if(abs(m_velocity.y) >=0.001f)
        {
            SetState(EntityState::Jumping);
        }
        else if(abs(m_velocity.x) >= 0.1f)
        {
            SetState(EntityState::Walking);
        }
        else
        {
            SetState(EntityState::Idle);
        }
    }
    else if(GetState() == EntityState::Attacking ||
    GetState() == EntityState::Hurt)
    {
        if(!m_spriteSheet.GetCurrentAnim()->IsPlaying())
        { SetState(EntityState::Idle);}
    }
    else if(GetState() == EntityState::Dying)
    {
        if(m_spriteSheet.GetCurrentAnim()->IsPlaying())
        {
            m_entityManager->Remove(m_id);
        }
    }
    Animate();
    m_spriteSheet.Update(l_dt);
    m_spriteSheet.SetSpritePosition(m_position);
}

void Character::Draw(sf::RenderWindow* l_wind)
{
    m_spriteSheet.Draw(l_wind);
}

void Character::Load(const std::string& l_path)
{
    std::ifstream file;
    file.open(l_path);
    if(!file.is_open())
    {
        std::cout << "Cannot open: " << l_path << std::endl;
    }
    std::string line;
    while(getline(file,line))
    {
        if(line[0] == '|')continue;
        std::stringstream keystream(line);
        std::string type;

        keystream >> type;
        if(type == "Name")
        {
            keystream >> m_name;
        }
        else if(type == "Spritesheet")
        {
            std::string path;
            keystream >> path;
            m_spriteSheet.LoadSheet("resources/media/SpriteSheets/" + path);
        } 
        else if(type == "Hitpoints")
        {
            keystream >> m_hitpoints;
        } 
        else if(type == "BoundingBox")
        {
            sf::Vector2f boundingSize;
            keystream >> boundingSize.x >> boundingSize.y;
            SetSize(boundingSize.x, boundingSize.y);
        } 
        else if(type == "DamageBox")
        {
            keystream >> m_attackAABBoffSet.x >> m_attackAABBoffSet.y 
            >> m_attackAABB.width >> m_attackAABB.height;
        } 
        else if(type == "Speed")
        {
            keystream >> m_speed.x >> m_speed.y;
        } 
        else if(type == "JumpVelocity")
        {
            keystream >> m_jumpVelocity;
        } 
        else if(type == "MaxVelocity")
        {
            keystream >> m_maxVelocity.x >> m_maxVelocity.y;
        }
        else 
        {
            std::cout << "! Unknown type in character file: "
            << type << std::endl;
        }
    }
    file.close();
}   
