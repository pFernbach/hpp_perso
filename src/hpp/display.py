

def displayRoadmap(prob,viewer) :
  white=[1.0,1.0,1.0,1.0]
  green=[0.23,0.75,0.2,0.5]
  yellow=[0.85,0.75,0.15,0.5]
  #creation node de la roadmap
  for i in range(0,len(prob.nodes())) :	
    name = "node%d" % i
    viewer.client.gui.addSphere(name,0.02,white);
    viewer.client.gui.addToGroup(name,viewer.sceneName);
    viewer.client.gui.addLandmark(name,0.1);
    viewer.client.gui.applyConfiguration(name,prob.nodes()[i]);


  #creation edge de la roadmap
  for i in range(0,prob.numberEdges()) : 
    name = "edge%d" % i
    viewer.client.gui.addLine(name,prob.edge(i)[0][0:3],prob.edge(i)[1][0:3],yellow)
    viewer.client.gui.addToGroup(name,viewer.sceneName);

  viewer.client.gui.refresh()

