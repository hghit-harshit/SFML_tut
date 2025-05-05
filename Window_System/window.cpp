#include "window.hpp"
#include <iostream>
Window::Window(){Setup("Window",sf::Vector2u{480,640});}

Window::Window(const std::string& title, const sf::Vector2u& size)
{
    Setup(title,size);
}

Window::~Window(){Destroy();}


void Window::Setup(const std::string& title, const sf::Vector2u& size)
{
    m_windowTitle = title;
    m_windowSize = size;
    m_isDone = false;
    m_isFullscreen = false;
    m_isFocused = true;
    m_eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullscreen, this);
    m_eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);
    Create();
}

void Window::Create()
{
    auto style = (m_isFullscreen ? sf::Style::Fullscreen :sf::Style::Default);
    m_window.create({m_windowSize.x,m_windowSize.y, 32},m_windowTitle,style);
    m_window.setFramerateLimit(200);
}

void Window::Destroy()
{
    m_window.close();
}

void Window::Update()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::LostFocus)
        {
            m_isFocused = false;
            m_eventManager.SetFocus(false);
        }
        else if(event.type == sf::Event::GainedFocus)
        {
            m_isFocused = true;
            m_eventManager.SetFocus(true);
        }

        m_eventManager.HandleEvent(event);
    }
    m_eventManager.Update();
}

void Window::ToggleFullscreen(EventDetails* l_details)
{
    std::cout << "is called\n";
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
}

void Window::BeginDraw(){m_window.clear(sf::Color::Black);}
void Window::EndDraw(){m_window.display();}


bool Window::IsDone(){return m_isDone;}
bool Window::IsFullscreen(){return m_isFullscreen;}
sf::Vector2u Window::GetWindowSize(){return m_windowSize;}
sf::RenderWindow* Window::GetRenderWindow()
{
    return &m_window;
}
void Window::Draw(sf::Drawable& drawable)
{
    m_window.draw(drawable);
}

EventManager* Window::GetEventManager(){return &m_eventManager;}

void Window::Close(EventDetails* l_details)
{
    std::cout<< "Close window is called\n";
    m_isDone = true;
}

sf::FloatRect Window::GetViewSpace()
{
    sf::Vector2f viewCenter = m_window.getView().getCenter();
    sf::Vector2f viewSize = m_window.getView().getSize();
    sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    return viewSpace;
}