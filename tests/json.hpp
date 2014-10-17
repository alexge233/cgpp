#ifndef _CGPP_JSON1_HPP_
#define _CGPP_JSON1_HPP_

#pragma once

const std::string json = "\
{\
    \"version\" : \"1\",\
    \"guid\" : \"00000000-0000-0000-0000-000000000000\",\
    \"creator\" : null,\
    \"relations\" : [\
     {\
         \"label\" : \"is\",\
         \"postag\" : \"VBZ\",\
         \"index\" : \"1\",\
         \"id\" : \"2976782025758403374\"\
     }],\
     \"concepts\" : [\
     {\
         \"label\" : \"sky\",\
         \"postag\" : \"NNZ\",\
         \"index\" : \"0\",\
         \"id\" : \"1577683746703680484\"\
     },\
     {\
         \"label\" : \"blue\",\
         \"postag\" : \"NNZ\",\
         \"index\" : \"2\",\
         \"id\" : \"15843861542616104093\"\
     }],\
     \"adjacencies\": [\
      {\
	\"nodeTo\" : \"2976782025758403374\",\
	\"nodeFrom\" : \"1577683746703680484\",\
	\"index\" : \"0\",\
	\"order\" : \"cr\"\
      },\
      {\
	\"nodeTo\" : \"15843861542616104093\",\
	\"nodeFrom\" : \"2976782025758403374\",\
	\"index\" : \"1\",\
	\"order\" : \"rc\"\
      }]\
}";


const std::string json1a = "{\"version\":\"1\",\"guid\":\"0badc008-4625-4741-870d-50b44e78ba8d\",\"creator\":\"null\",\"relations\":[{\"label\":\"over\",\"id\":\"1645448654\",\"index\":\"1\",\"postag\":\"NA\"},{\"label\":\"for\",\"id\":\"568510665\",\"index\":\"3\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"Arrogance\",\"id\":\"1731870828\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"need\",\"id\":\"73710766\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"sleep\",\"id\":\"1174270378\",\"index\":\"4\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"1731870828\",\"nodeTo\":\"1645448654\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"1645448654\",\"nodeTo\":\"73710766\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"73710766\",\"nodeTo\":\"568510665\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"568510665\",\"nodeTo\":\"1174270378\",\"index\":\"1\",\"order\":\"rc\"}]}";

const std::string json1b = "{\"version\":\"1\",\"guid\":\"0badc008-4625-4741-870d-50b44e78ba8d\",\"creator\":\"null\",\"relations\":[{\"label\":\"over\",\"id\":\"1645448654\",\"index\":\"1\",\"postag\":\"NA\"},{\"label\":\"for\",\"id\":\"568510665\",\"index\":\"3\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"Ignorance\",\"id\":\"1731870828\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"need\",\"id\":\"73710766\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"sleep\",\"id\":\"1174270378\",\"index\":\"4\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"1731870828\",\"nodeTo\":\"1645448654\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"1645448654\",\"nodeTo\":\"73710766\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"73710766\",\"nodeTo\":\"568510665\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"568510665\",\"nodeTo\":\"1174270378\",\"index\":\"1\",\"order\":\"rc\"}]}";

const std::string json1c = "{\"version\":\"1\",\"guid\":\"0badc008-4625-4741-870d-50b44e78ba8d\",\"creator\":\"null\",\"relations\":[{\"label\":\"over\",\"id\":\"1645448654\",\"index\":\"1\",\"postag\":\"NA\"},{\"label\":\"for\",\"id\":\"568510665\",\"index\":\"3\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"Arrogance\",\"id\":\"1731870828\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"need\",\"id\":\"73710766\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"sleep\",\"id\":\"1174270378\",\"index\":\"4\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"1645448654\",\"nodeTo\":\"73710766\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"1731870828\",\"nodeTo\":\"1645448654\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"73710766\",\"nodeTo\":\"568510665\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"568510665\",\"nodeTo\":\"1174270378\",\"index\":\"1\",\"order\":\"rc\"}]}";

const std::string json2a = "{\"version\":\"1\",\"guid\":\"92a02930-04ea-48ae-877c-d7addecc08d4\",\"creator\":\"null\",\"relations\":[{\"label\":\"off\",\"id\":\"1884867608\",\"index\":\"1\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"Asthma\",\"id\":\"2778785166\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"national\",\"id\":\"1351770505\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"agenda\",\"id\":\"374018279\",\"index\":\"3\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"2778785166\",\"nodeTo\":\"1884867608\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"1351770505\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"374018279\",\"index\":\"2\",\"order\":\"rc\"}]}";

const std::string json2b = "{\"version\":\"1\",\"guid\":\"92a02930-04ea-48ae-877c-d7addecc08d4\",\"creator\":\"null\",\"relations\":[{\"label\":\"off\",\"id\":\"1884867608\",\"index\":\"1\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"Asthma\",\"id\":\"2778785166\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"national\",\"id\":\"1351770505\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"agenda\",\"id\":\"374018279\",\"index\":\"3\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"2778785166\",\"nodeTo\":\"1884867608\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"374018279\",\"index\":\"2\",\"order\":\"rc\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"1351770505\",\"index\":\"1\",\"order\":\"rc\"}]}";

const std::string json2c = "{\"version\":\"1\",\"guid\":\"92a02930-04ea-48ae-877c-d7addecc08d4\",\"creator\":\"null\",\"relations\":[{\"label\":\"off\",\"id\":\"1884867608\",\"index\":\"1\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"Asthma\",\"id\":\"2778785166\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"national\",\"id\":\"1351770505\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"agenda\",\"id\":\"374018279\",\"index\":\"3\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"1351770505\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"2778785166\",\"nodeTo\":\"1884867608\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"374018279\",\"index\":\"2\",\"order\":\"rc\"}]}";

const std::string json2d = "{\"version\":\"1\",\"guid\":\"92a02930-04ea-48ae-877c-d7addecc08d4\",\"creator\":\"null\",\"relations\":[{\"label\":\"off\",\"id\":\"1884867608\",\"index\":\"1\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"Asthma\",\"id\":\"2778785166\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"national\",\"id\":\"1351770505\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"agenda\",\"id\":\"374018279\",\"index\":\"3\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"1351770505\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"374018279\",\"index\":\"2\",\"order\":\"rc\"},{\"nodeFrom\":\"2778785166\",\"nodeTo\":\"1884867608\",\"index\":\"1\",\"order\":\"cr\"}]}";

const std::string json2e = "{\"version\":\"1\",\"guid\":\"92a02930-04ea-48ae-877c-d7addecc08d4\",\"creator\":\"null\",\"relations\":[{\"label\":\"off\",\"id\":\"1884867608\",\"index\":\"1\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"national\",\"id\":\"1351770505\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"Asthma\",\"id\":\"2778785166\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"agenda\",\"id\":\"374018279\",\"index\":\"3\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"2778785166\",\"nodeTo\":\"1884867608\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"1351770505\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"374018279\",\"index\":\"2\",\"order\":\"rc\"}]}";

const std::string json2f = "{\"version\":\"1\",\"guid\":\"92a02930-04ea-48ae-877c-d7addecc08d4\",\"creator\":\"null\",\"relations\":[{\"label\":\"off\",\"id\":\"1884867608\",\"index\":\"1\",\"postag\":\"NA\"}],\"concepts\":[{\"label\":\"national\",\"id\":\"1351770505\",\"index\":\"2\",\"postag\":\"NA\"},{\"label\":\"Cancer\",\"id\":\"2778785166\",\"index\":\"0\",\"postag\":\"NA\"},{\"label\":\"agenda\",\"id\":\"374018279\",\"index\":\"3\",\"postag\":\"NA\"}],\"adjacencies\":[{\"nodeFrom\":\"2778785166\",\"nodeTo\":\"1884867608\",\"index\":\"1\",\"order\":\"cr\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"1351770505\",\"index\":\"1\",\"order\":\"rc\"},{\"nodeFrom\":\"1884867608\",\"nodeTo\":\"374018279\",\"index\":\"2\",\"order\":\"rc\"}]}";



#endif
