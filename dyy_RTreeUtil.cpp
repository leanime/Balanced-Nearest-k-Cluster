#include "dyy_RTreeUtil.hpp"
#include <queue>


namespace dyy{


Point RStarTreeUtil::NNquery(RStarTree &tree, Point &point)
{
    
    std::priority_queue<PDEntry, std::vector<PDEntry>, PDEntry::ascending> pq;
    pq.push(PDEntry(tree.root,1));

    double mindist = std::numeric_limits<double>::max();
    Point *NN_point = nullptr;

    while(!pq.empty()){
        PDEntry e = pq.top();
//        std::cout << "top dis1: " << pq.top().dis << std::endl;
//        std::cout << "top level: " << pq.top().nodePtr->level << std::endl;
        pq.pop();

        if(e.nodePtr->level){ //non leaf
            Node_P_V &children = *e.nodePtr->children;
            for(size_t ic = 0; ic < children.size(); ic++){
                Node_P childptr = children.at(ic);
                double dis = minDis2(point, childptr->mbrn);
               // std::cout << "node level: " << e.nodePtr->level << std::endl;
               // std::cout << "tree dis1: " << dis << std::endl;
                if(dis < mindist){
                    pq.push(PDEntry(childptr,dis));
                }
            }
        } else { // leaf
            //e.nodePtr->mbrn.print();
            Entry_P_V &entries = *e.nodePtr->entries;
            for(size_t ie = 0; ie < entries.size(); ie++){
                Entry_P entryPtr = entries.at(ie);
                double dis = dis2(point, entryPtr->mbre);
                //std::cout << "tree dis: " << dis << std::endl;
                if(dis < mindist){
                    mindist = dis;
//                    std::cout << "tree dis: " << dis << std::endl;
                    NN_point = static_cast<Point *>(entryPtr->data);
                    
                }
            }
//           NN_point->print();
        }
    }
//    std::cout << "mindis: " << mindist << std::endl;
    return *NN_point;
}


    
    
   Point_Map RStarTreeUtil::kNNquery(RStarTree &tree, Point &point, int k){
//        const auto startTime = std::chrono::system_clock::now();
       
        Point_Map kNN_Points;
       
        std::priority_queue<PDEntry, std::vector<PDEntry>, PDEntry::ascending> pq;
        pq.push(PDEntry(tree.root,1));
        double mindist = std::numeric_limits<double>::max();
           // std::cout << i << std::endl;
         
        while(!pq.empty()){
            
           // std::cout << j << std::endl;
            
            PDEntry e = pq.top();
            pq.pop();
            
            
            if(e.nodePtr->level){ //non leaf
                Node_P_V &children = *e.nodePtr->children;
                for(size_t ic = 0; ic < children.size(); ic++){
                    Node_P childptr = children.at(ic);
                    double dis = minDis2(point, childptr->mbrn);
        
                   // std::cout << "tree dis2: " << dis << std::endl;
                    if(dis < mindist){
                        pq.push(PDEntry(childptr,dis));
                    }
                }
            } else { // leaf
                Entry_P_V &entries = *e.nodePtr->entries;
                
              //  if(i>=97){std::cout << "ok" << std::endl;}
                
                for(size_t ie = 0; ie < entries.size(); ie++){
                    Entry_P entryPtr = entries.at(ie);
                    //entryPtr->mbre.print();
                    double dis = dis2(point, entryPtr->mbre);
                        //std::cout << "tree dis: " << dis << std::endl;
                    if(kNN_Points.size()<k){
                        if(kNN_Points.count(dis)>0){
                            if(kNN_Points.find(dis)->second.equal(*static_cast<Point *>(entryPtr->data)))
                            continue;
                            else
                            kNN_Points.insert(std::pair<double, Point>(dis, *static_cast<Point *>(entryPtr->data))) ;
                        }
                        else{
                            kNN_Points.insert(std::pair<double, Point>(dis, *static_cast<Point *>(entryPtr->data))) ;
                        }
                        if(kNN_Points.size()==k){
                             mindist=kNN_Points.rbegin()->first;
                        }
                    }
                    else{
                        if(dis<mindist){
                            if(kNN_Points.count(dis)>0){
                                if(kNN_Points.find(dis)->second.equal(*static_cast<Point *>(entryPtr->data)))
                                    continue;
                                else{
                                kNN_Points.erase(mindist);
                                kNN_Points.insert(std::pair<double, Point>(dis, *static_cast<Point *>(entryPtr->data)));
                                mindist=kNN_Points.rbegin()->first;
                                }
                            }
                            else{
                            kNN_Points.erase(mindist);
                            kNN_Points.insert(std::pair<double, Point>(dis, *static_cast<Point *>(entryPtr->data)));
                            mindist=kNN_Points.rbegin()->first;
                            }
                        }
                    }
            }
            }
      }
        
//        const auto endTime = std::chrono::system_clock::now();
//        const auto timeSpan = endTime - startTime;
//        std::cout << "rtree knn processing time:" << std::chrono::duration_cast<std::chrono::milliseconds>(timeSpan).count() << "[ms]"<<std::endl;
        return kNN_Points;
      
    }
    
   
    
    Point_Map RStarTreeUtil::QuerykNNquery(RStarTree &tree, Point &point, int k, double querybound){
        
        Point_Map kNN_Points;
        
        std::priority_queue<PDEntry, std::vector<PDEntry>, PDEntry::ascending> pq;
        pq.push(PDEntry(tree.root,1));
        double mindist = std::numeric_limits<double>::max();
        // std::cout << i << std::endl;
        
        while(!pq.empty()){
            
            // std::cout << j << std::endl;
            
            PDEntry e = pq.top();
            pq.pop();
            
            
            if(e.nodePtr->level){ //non leaf
                Node_P_V &children = *e.nodePtr->children;
                for(size_t ic = 0; ic < children.size(); ic++){
                    Node_P childptr = children.at(ic);
                    double dis = minDis2(point, childptr->mbrn);
                    
                    // std::cout << "tree dis2: " << dis << std::endl;
                    if(dis < mindist && dis< querybound){
                        pq.push(PDEntry(childptr,dis));
                    }
                }
            } else { // leaf
                Entry_P_V &entries = *e.nodePtr->entries;
                
                //  if(i>=97){std::cout << "ok" << std::endl;}
                
                for(size_t ie = 0; ie < entries.size(); ie++){
                    Entry_P entryPtr = entries.at(ie);
                    //entryPtr->mbre.print();
                    double dis = dis2(point, entryPtr->mbre);
                    /* if(i>=97){
                     std::cout << "tree dis: " << dis << std::endl;
                     }*/
                    if(kNN_Points.size()<k){
                        kNN_Points.insert(std::pair<double, Point>(dis, *static_cast<Point *>(entryPtr->data))) ;
                     
                        if(kNN_Points.size()==k){
                            mindist=kNN_Points.rbegin()->first;
                        }
                    }
                    else{
                        if(dis<mindist){
                            kNN_Points.erase(mindist);
                            kNN_Points.insert(std::pair<double, Point>(dis, *static_cast<Point *>(entryPtr->data)));
                            mindist=kNN_Points.rbegin()->first;
                        }
                    }
                }
            }
        }
    
        return kNN_Points;
    }
    
    

}/*dyy*/
