#pragma once

class ResourceStack{
    
    private:
        float m_resources = 0;

    public:
        void addResources(float amount); 
        void removeResources(float amount);    
        void clearResources();
        float getResources();
};