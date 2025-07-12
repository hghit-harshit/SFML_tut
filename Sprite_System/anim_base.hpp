// The base animations class
#pragma once
#include <sstream>
// forward declaration
class SpriteSheet;
using Frame = unsigned int;

class Anim_Base
{
    friend class SpriteSheet;

    public:
        Anim_Base();
        virtual ~Anim_Base();

        // Setter and getters
        void SetSpriteSheet(SpriteSheet* l_sheet);

        void SetFrame(const Frame& l_frame);
        void SetStartFrame(Frame l_frame);
        void SetEndFrame(Frame l_frame);
        void SetFrameRow(unsigned int l_row);
        void SetActionStart(Frame l_frame);
        void SetActionEnd(Frame l_frame);
        void SetFrameTime(float l_time);
        void SetLooping(bool l_loop);
        void SetName(const std::string& l_name);

       	SpriteSheet* GetSpriteSheet();

        Frame GetFrame() const;
        Frame GetStartFrame() const;
        Frame GetEndFrame() const;
        unsigned int GetFrameRow() const;
        int GetActionStart() const;
        int GetActionEnd() const;
        float GetFrameTime() const;
        float GetElapsedTime() const;
        bool IsLooping() const;
        bool IsPlaying() const;
        bool IsInAction() const;
        bool CheckMoved();
        std::string GetName() const;

        bool IsInAction();
        void Play();
        void Pause();
        void Stop();
        void Reset();


        virtual void Update(const float& l_dt);

        friend std::stringstream& operator>>(
            std::stringstream& l_stream, Anim_Base& a)
            {
                a.ReadIn(l_stream);
                return l_stream;
            }

    protected:
        virtual void FrameStep()   = 0; // to update frames
        virtual void  CropSprite() = 0; // to obtain the sprites for the animation  
        virtual void  ReadIn(std::stringstream& l_stream) = 0; // to load data from file

        Frame m_frameCurrent;
        Frame m_frameStart;
        Frame m_frameEnd;
        Frame m_frameRow;
        int   m_frameActionStart; // frame for the beginning of an action
        int   m_frameActionEnd; // frame for the ...u guessed it.. end of an action
        // Action defines a range of frames during which a 
        // behavior which is specific to that animation can be performed. 
        //If it's set to negative 
        // one, this behavior can be performed throughout the entire animation.

        float m_frameTime; //time taken by each frame to finish
        float m_elapsedTime;
        bool m_loop;
        bool m_playing;
        std::string m_name;
        SpriteSheet* m_spriteSheet;
};