#pragma once
#include <iostream>
#include <chrono>
#include <map>
#include <memory>
#include "DynamicExperimentalMeasurement.h"
#include "ExperimentalMeasurement.h"
#include "IDataInitializer.h"

class Experimentor{
private:
    int m_MaxRuns;
    int m_IncStep;
    std::vector<std::unique_ptr<IExperimentalMeasurement>> m_Results;

    public:
        Experimentor(int max, int incStep)
        :m_MaxRuns(max)
        ,m_IncStep(incStep)
        {}
        ~Experimentor(){}
        bool Execute(
             std::function<std::unique_ptr<IDataInitializer>(int)> init,
             std::map<std::string,std::function<void(IDataInitializer* )> > &
             experiments){
            m_Results.clear();
            return DoExecute(init, experiments);
            }
        bool Execute(
            std::function<std::unique_ptr<IDataInitializer>(int)> init,
            std::function<void(IDataInitializer*)> first, 
            std::function<void(IDataInitializer*)> second){

            m_Results.clear();

            std::map<std::string,std::function<void(IDataInitializer* )>> testFunctions;
            testFunctions["First"] = first;
            testFunctions["Second"] = second;

            return DoExecute(init, testFunctions);
        }

    private:

        bool DoExecute(std::function<std::unique_ptr<IDataInitializer>(int)> init,
             std::map<std::string,std::function<void(IDataInitializer* )> > &experiments){

            std::vector<float> ratio;
            int loop = 0;
            for(int i = 3; i < m_MaxRuns;){
                std::cout << "Loop #" << loop ++ << std::endl;
                m_Results.push_back(experiment(i,init,experiments));
                i+= m_IncStep;
            }

            loop = 0;

            for(auto &result : m_Results){

                std::cout << "Loop #" << loop <<  "=>" << result->get(0) << " / " << result->get(1) << std::endl;
                loop++;

                result->calculate(ratio);
            }

            //Average of all ratios
            float sum = 0;
            for(auto &r : ratio){
                sum += r;
            }

            std::vector<std::string> labels;
            if(!m_Results.empty()){
                m_Results[0]->getLabels(labels);
                float res = (float) ( (float) sum / ratio.size() ) ;
                std::string fastOrSlow("slower");
                if(res >0 ){
                    fastOrSlow = "faster";
                }
                std::cout << labels[0] << " is " << res << " "<< fastOrSlow << " " << "than " << labels[1] << std::endl;
            }
            return true;
        }

        std::chrono::high_resolution_clock::time_point getTimeNow(){
            return std::chrono::high_resolution_clock::now();
        }

        std::unique_ptr<IExperimentalMeasurement> experiment(int size, 
            std::function<std::unique_ptr<IDataInitializer>(int)> &init,
            std::map<std::string,std::function<void(IDataInitializer* )> >
            &experiments){

            auto res = init(size);
            std::cout << "Buffer size =>"<<res->size() << " elements" << std::endl;

            std::unique_ptr<IExperimentalMeasurement> m = std::unique_ptr<IExperimentalMeasurement>(new DynamicExperimentalMeasurement);
            std::string label;

            for (auto &exp : experiments){
                auto start = this->getTimeNow();
                exp.second(res.get());
                auto finish = this->getTimeNow();
                label = exp.first;
                m->add(label, std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count());
            }
            return m;
        }
};
