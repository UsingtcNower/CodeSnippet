vi D(N, 987654321); 
      // distance from start vertex to each vertex

      priority_queue<ii,vector<ii>, greater<ii> > Q; 
      // priority_queue with reverse comparison operator, 
      // so top() will return the least distance
      // initialize the start vertex, suppose it’s zero
      D[0] = 0;
      Q.push(ii(0,0));

      // iterate while queue is not empty
      while(!Q.empty()) {

            // fetch the nearest element
            ii top = Q.top();
            Q.pop();
                        
            // v is vertex index, d is the distance
            int v = top.second, d = top.first;

            // this check is very important
            // we analyze each vertex only once
            // the other occurrences of it on queue (added earlier) 
            // will have greater distance
            if(d <= D[v]) {
                  // iterate through all outcoming edges from v
                  tr(G[v], it) {
                        int v2 = it->first, cost = it->second;
                        if(D[v2] > D[v] + cost) {
                              // update distance if possible
                              D[v2] = D[v] + cost;
                              // add the vertex to queue
                              Q.push(ii(D[v2], v2));

                        }
                  }
            }
      }
