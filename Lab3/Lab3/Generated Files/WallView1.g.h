﻿#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------


namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class TextBlock;
                ref class TextBox;
                ref class Button;
                ref class Image;
            }
        }
    }
}

namespace Lab3
{
    [::Windows::Foundation::Metadata::WebHostHidden]
    partial ref class WallView1 : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector,
        public ::Windows::UI::Xaml::Markup::IComponentConnector2
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
        virtual ::Windows::UI::Xaml::Markup::IComponentConnector^ GetBindingConnector(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textBlock1;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textBlock;
        private: ::Windows::UI::Xaml::Controls::TextBox^ Title;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textBlock2;
        private: ::Windows::UI::Xaml::Controls::TextBox^ Description;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textBlock4;
        private: ::Windows::UI::Xaml::Controls::TextBox^ Area;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textBlock6;
        private: ::Windows::UI::Xaml::Controls::Button^ ChangePicture;
        private: ::Windows::UI::Xaml::Controls::Image^ WallImage;
        private: ::Windows::UI::Xaml::Controls::Button^ Save;
        private: ::Windows::UI::Xaml::Controls::Button^ Back;
    };
}

