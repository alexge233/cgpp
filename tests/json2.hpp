#ifndef _CGPP_JSON2_HPP_
#define _CGPP_JSON3_HPP_
#pragma once

const std::string json2 = "\
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
         \"label\" : \"blue\",\
         \"postag\" : \"NNZ\",\
         \"index\" : \"2\",\
         \"id\" : \"15843861542616104093\"\
     },\
     {\
         \"label\" : \"sky\",\
         \"postag\" : \"NNZ\",\
         \"index\" : \"0\",\
         \"id\" : \"1577683746703680484\"\
     }],\
     \"adjacencies\": [\
     {\
        \"nodeTo\" : \"15843861542616104093\",\
        \"nodeFrom\" : \"2976782025758403374\",\
        \"index\" : \"1\",\
        \"order\" : \"rc\"\
      },\
      {\
        \"nodeTo\" : \"2976782025758403374\",\
        \"nodeFrom\" : \"1577683746703680484\",\
        \"index\" : \"0\",\
        \"order\" : \"cr\"\
      }]\
}";

#endif
