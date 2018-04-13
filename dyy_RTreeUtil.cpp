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


    
    
    Point_V RStarTreeUtil::kNNquery(RStarTree &tree, Point &point, int k){
        
        int j=0;
        
        Point_V pA_V;
        double minmindist = -std::numeric_limits<double>::min();

        
        for(int i=0;i<k;i++){
            
            Point *NN_point = nullptr;
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
                    double maxdis = maxDis2(point, childptr->mbrn);
                   // std::cout << "tree dis2: " << dis << std::endl;
                    if(minmindist < maxdis &&dis < mindist){
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
                    if(minmindist < dis && dis < mindist){
                        mindist = dis;
                        NN_point = static_cast<Point *>(entryPtr->data);
                        
                    }
                    
                }
            }
            
            j++;
         }
       
            
            if(mindist<std::numeric_limits<double>::max()){
            //NN_point->print();
            
            pA_V.push_back(*NN_point);
          //  std::cout << "mindis: " << mindist << std::endl;
           // std::cout << "————————"<< std::endl;
            minmindist=mindist;
            }
            else
                break;
        }
        

        return pA_V;
      
    }
    
    
    Point_V RStarTreeUtil::QuerykNNquery(RStarTree &tree, Point &point, int k, double querybound){
        int j=0;
        Point_V pA_V;
        double minmindist = -std::numeric_limits<double>::min();
       // bool flag=0;
        for(int i=0;i<tree.root->aggregate;i++){
            if(!pA_V.empty()){
              if(pA_V.back().distance(point)>querybound){
                return pA_V;
              }
            }
            Point *NN_point = nullptr;
            std::priority_queue<PDEntry, std::vector<PDEntry>, PDEntry::ascending> pq;
            pq.push(PDEntry(tree.root,1));
            double mindist = std::numeric_limits<double>::max();
            // std::cout << i << std::endl;
            //std::cout << "------- " << i<< std::endl;
            while(!pq.empty()){
                
                PDEntry e = pq.top();
               //std::cout << "pq.top().dis: " <<pq.top().dis  << std::endl;
               
                //std::cout << "~~~~ " << std::endl;
                pq.pop();
                
                if(e.nodePtr->level){ //non leaf
                
                    Node_P_V &children = *e.nodePtr->children;
                    for(size_t ic = 0; ic < children.size(); ic++){
                        Node_P childptr = children.at(ic);
                        double dis = minDis2(point, childptr->mbrn);
                        double maxdis = maxDis2(point, childptr->mbrn);
                        //std::cout << "tree dis2: " << dis << std::endl;
                            if(minmindist < maxdis && dis < mindist && dis<querybound){
                               // std::cout << "count1: " << ic << std::endl;
                                pq.push(PDEntry(childptr,dis));
                        }
                    }
              
                   // std::cout << "========" << std::endl;
                }
                else { // leaf
                    //std::cout << "dis" <<mindist<< std::endl;
                    Entry_P_V &entries = *e.nodePtr->entries;
                    for(size_t ie = 0; ie < entries.size(); ie++){
                        Entry_P entryPtr = entries.at(ie);
                        double dis = dis2(point, entryPtr->mbre);
                        if(minmindist < dis && dis < mindist){
                            mindist = dis;
                            NN_point = static_cast<Point *>(entryPtr->data);
                           // NN_point->print();
                            j++;
                        }
                   }
                 //std::cout << "size" <<pA_V.size()<< std::endl;
                    
                }
                
            }
            
            if(mindist<std::numeric_limits<double>::max()){
                //NN_point->print();
                
                pA_V.push_back(*NN_point);
                //  std::cout << "mindis: " << mindist << std::endl;
                // std::cout << "————————"<< std::endl;
                minmindist=mindist;
            }
          
            
        }
         //std::cout << "j"<<j << std::endl;
        return pA_V;
    }
    
    

}/*dyy*/
