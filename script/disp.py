


white=[1.0,1.0,1.0,1.0]
green=[0.23,0.75,0.2,0.5]
yellow=[0.85,0.75,0.15,0.5]
#creation node de la roadmap
for i in range(0,len(ps.nodes())) :	
  name = "node%d" % i
  v.client.gui.addSphere(name,0.02,white);
  v.client.gui.addToGroup(name,v.sceneName);
  v.client.gui.addLandmark(name,0.1);
  v.client.gui.applyConfiguration(name,ps.nodes()[i]);


#creation edge de la roadmap
for i in range(0,ps.numberEdges()) : 
  name = "edge%d" % i
  v.client.gui.addLine(name,ps.edge(i)[0][0:3],ps.edge(i)[1][0:3],yellow)
  v.client.gui.addToGroup(name,v.sceneName);

v.client.gui.refresh()

