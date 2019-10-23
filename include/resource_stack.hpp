#pragma once

class ResourceStack{
    
    private:
        long double m_resources = 0;

    public:
        ResourceStack(long double startingResources);
        void addResources(long double amount); 
        bool removeResources(long double amount);    
        void clearResources();
        long double getResources();
};