#pragma once

class ResourceStack{
    
    private:
        float m_resources = 0;

    public:
        ResourceStack(float startingResources);
        void addResources(float amount); 
        bool removeResources(float amount);    
        void clearResources();
        float getResources();
};