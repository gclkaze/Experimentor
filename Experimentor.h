#pragma once
#include <iostream>
#include <chrono>
#include <map>
#include <memory>
#include <vector>

struct measurement{
    int t1;
    int t2;
    ~measurement(){}
};

struct dyn_measurement{
    std::vector<int> t;
    ~dyn_measurement(){}
};


class Experimentor{
private:
    int m_MaxRuns;
    int m_IncStep;
    std::vector<std::unique_ptr<measurement>> m_Results;

    public:
        Experimentor(int max, int incStep)
        :m_MaxRuns(max)
        ,m_IncStep(incStep)
        {}
        ~Experimentor(){}
        bool Execute(
            std::function<std::vector<int>*(int)> init,
            std::function<void(std::vector<int>* )> first, 
            std::function<void(std::vector<int>* )> second){

            std::vector<std::unique_ptr<measurement>> results;
            std::vector<float> ratio;

            int loop = 0;
            for(int i = 3; i < m_MaxRuns;){
                std::cout << "Loop #" << loop ++ << std::endl;
                results.push_back(experiment(i,init,first, second));
                i+= m_IncStep;
            }

            loop = 0;

            for(auto &result : results){

                std::cout << "Loop #" << loop <<  "=>" << result->t1 << " / " << result->t2 << std::endl;
                loop++;

                if( result->t2){
                    ratio.push_back((float)((float)result->t1 / result->t2)) ;
                    std::cout << (float)((float)result->t1 / result->t2) << std::endl;
                }
            }

            //Average of all ratios
            float sum = 0;
            for(auto &r : ratio){
                sum += r;
            }
            std::cout << "Parallel is "<< sum << " / " << ratio.size() << " times faster than sequential" << std::endl;
            std::cout << "Parallel is "<< (float) ( (float) sum / ratio.size() ) << " times faster than sequential" << std::endl;
            return true;
        }
    private:
        std::unique_ptr<struct measurement> experiment(int size, 
            std::function<std::vector<int>*(int)> init,
            std::function<void(std::vector<int>* )> first, 
            std::function<void(std::vector<int>* )> second){

            auto v = init(size);
            std::cout << "Buffer size =>"<<v->size() << " elements" << std::endl;
            auto start = getTimeNow();
            
            {
                first(v);
            }

            auto finish = getTimeNow();
            int diff1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
            start = getTimeNow();

            {
                second(v);
            }
            
            finish = getTimeNow();
            int diff2 = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();

            std::unique_ptr<struct measurement> m = std::unique_ptr<struct measurement>(new struct measurement);
            m->t1 = diff2;
            m->t2 = diff1;
            std::cout << diff1 << " vs " << diff2 << " for " << size << " elements.." << std::endl;
            return m;
        }

        std::chrono::high_resolution_clock::time_point getTimeNow(){
            return std::chrono::high_resolution_clock::now();
        }

        std::unique_ptr<struct dyn_measurement> experiment(int size, 
            std::function<std::vector<int>*(int)> init,
            std::map<std::string,std::function<void(std::vector<int>* )> >
            experiments){

            auto v = init(size);
            std::cout << "Buffer size =>"<<v->size() << " elements" << std::endl;

            std::unique_ptr<struct dyn_measurement> m = std::unique_ptr<struct dyn_measurement>(new struct dyn_measurement);

            for (auto &exp : experiments){
                auto start = this->getTimeNow();
                exp.second(v);
                auto finish = this->getTimeNow();
                m->t.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());
            }
            return m;
        }
};
