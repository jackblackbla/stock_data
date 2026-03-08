/************************************************************************************
	주의

	이 자료는 2025년 9월 30일 기준 자료이며 향후 변경될 가능성이 있습니다.
	자료 구조가 맞지 않을 경우 구조체가 변경되지 않았는지 우선 확인하시기 바랍니다.

	최신 자료는 웹페이지를 통해 안내되며 자동 안내(OpenAPI 접속시)를 하고 있으니 
	반드시 게시를 확인하시기 바랍니다.

************************************************************************************/

typedef struct tagf1InBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} Tf1InBlock;

typedef struct tagf1OutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char fuhotime                         [  8];   //시간                 
	char fuoffer                          [  9];   //매도우선호가         
	char fubid                            [  9];   //매수우선호가         
	char fuofferjan                       [  6];   //매도우선잔량         
	char fubidjan                         [  6];   //매수우선잔량         
	char fujoffer                         [  9];   //차선매도호가         
	char fujbid                           [  9];   //차선매수호가         
	char fujofferjan                      [  6];   //차선매도잔량         
	char fujbidjan                        [  6];   //차선매수잔량         
	char fujjoffer                        [  9];   //차차선매도호가       
	char fujjbid                          [  9];   //차차선매수호가       
	char fujjofferjan                     [  6];   //차차선매도잔량       
	char fujjbidjan                       [  6];   //차차선매수잔량       
	char futofferjan                      [  6];   //총매도잔량           
	char futbidjan                        [  6];   //총매수잔량           
	char fuj4offer                        [  9];   //4차선매도호가        
	char fuj4bid                          [  9];   //4차선매수호가        
	char fuj4offerjan                     [  6];   //4차선매도잔량        
	char fuj4bidjan                       [  6];   //4차선매수잔량        
	char fuj5offer                        [  9];   //5차선매도호가        
	char fuj5bid                          [  9];   //5차선매수호가        
	char fuj5offerjan                     [  6];   //5차선매도잔량        
	char fuj5bidjan                       [  6];   //5차선매수잔량        
	char fuoffersu                        [  4];   //우선매도건수         
	char fujoffersu                       [  4];   //차선매도건수         
	char fujjoffersu                      [  4];   //차차선매도건수       
	char fuj4offersu                      [  4];   //4차선매도건수        
	char fuj5offersu                      [  4];   //5차선매도건수        
	char futoffersu                       [  5];   //총매도건수           
	char fubidsu                          [  4];   //우선매수건수         
	char fujbidsu                         [  4];   //차선매수건수         
	char fujjbidsu                        [  4];   //차차선매수건수       
	char fuj4bidsu                        [  4];   //4차선매수건수        
	char fuj5bidsu                        [  4];   //5차선매수건수        
	char futbidsu                         [  5];   //총매수건수           
} Tf1OutBlock;

typedef struct tagf1
{
	Tf1InBlock                        f1inblock                             ;  //입력 
	Tf1OutBlock                       f1outblock                            ;  //출력 
} Tf1;

typedef struct tagf3InBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} Tf3InBlock;

typedef struct tagf3OutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char futheoryprice                    [  9];   //선물이론가           
	char futheorytime                     [  8];   //이론가시간           
	char fugrate                          [  9];   //괴리도               
	char fugratio                         [  5];   //괴리율               
} Tf3OutBlock;

typedef struct tagf3
{
	Tf3InBlock                        f3inblock                             ;  //입력 
	Tf3OutBlock                       f3outblock                            ;  //출력 
} Tf3;

typedef struct tagf4InBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} Tf4InBlock;

typedef struct tagf4OutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char fuchetime                        [  8];   //체결시간             
	char fuopenyak                        [  7];   //미결제약정수량       
	char fupreopenyak                     [  7];   //전일미결제약정수량   
} Tf4OutBlock;

typedef struct tagf4
{
	Tf4InBlock                        f4inblock                             ;  //입력 
	Tf4OutBlock                       f4outblock                            ;  //출력 
} Tf4;

typedef struct tagf8InBlock    //입력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
} Tf8InBlock;

typedef struct tagf8OutBlock    //출력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
	char fuchetime                        [  8];	char _fuchetime;                          //시간                 
	char fusign                           [  1];	char _fusign;                             //등락부호             
	char fuchange                         [  9];	char _fuchange;                           //등락폭               
	char fucurr                           [  9];	char _fucurr;                             //현재가               
	char fuhigh                           [  9];	char _fuhigh;                             //고가                 
	char fulow                            [  9];	char _fulow;                              //저가                 
	char fuvol                            [  6];	char _fuvol;                              //체결수량             
	char fuvolall                         [  7];	char _fuvolall;                           //누적체결수량         
	char fuvalall                         [ 12];	char _fuvalall;                           //누적거래대금         
	char fuopenyak                        [  7];	char _fuopenyak;                          //미결제약정수량       
	char fuoffer                          [  9];	char _fuoffer;                            //우선매도호가         
	char fubid                            [  9];	char _fubid;                              //우선매수호가         
	char fuofferjan                       [  6];	char _fuofferjan;                         //우선매도잔량         
	char fubidjan                         [  6];	char _fubidjan;                           //우선매수잔량         
	char futofferjan                      [  6];	char _futofferjan;                        //총매도잔량           
	char futbidjan                        [  6];	char _futbidjan;                          //총매수잔량           
	char fuoffersu                        [  4];	char _fuoffersu;                          //우선매도건수         
	char fubidsu                          [  4];	char _fubidsu;                            //우선매수건수         
	char futoffersu                       [  5];	char _futoffersu;                         //총매도건수           
	char futbidsu                         [  5];	char _futbidsu;                           //총매수건수           
	char fuchrate                         [  5];	char _fuchrate;                           //등락률               
	char fubasis                          [  9];	char _fubasis;                            //베이시스             
	char fugrate                          [  9];	char _fugrate;                            //괴리도               
	char fugratio                         [  5];	char _fugratio;                           //괴리율               
	char fupreopenyak                     [  7];	char _fupreopenyak;                       //미결제약정전일       
	char fuspvolall                       [  7];	char _fuspvolall;                         //스프레드수량         
	char fuopen                           [  9];	char _fuopen;                             //시가                 
	char bulkvol                          [  7];	char _bulkvol;                            //협의대량누적체결수량 
} Tf8OutBlock;

typedef struct tagf8
{
	Tf8InBlock                        f8inblock                             ;  //입력 
	Tf8OutBlock                       f8outblock                            ;  //출력 
} Tf8;

typedef struct tagq1InBlock    //입력
{
	char fuspcode                         [  8];   //종목코드             
} Tq1InBlock;

typedef struct tagq1OutBlock    //출력
{
	char fuspcode                         [  8];   //종목코드             
	char fusphotime                       [  8];   //시간                 
	char fuspoffer                        [  6];   //우선매도호가         
	char fuspbid                          [  6];   //우선매수호가         
	char fuspofferjan                     [  6];   //우선매도잔량         
	char fuspbidjan                       [  6];   //우선매수잔량         
	char fuspjoffer                       [  6];   //차선매도호가         
	char fuspjbid                         [  6];   //차선매수호가         
	char fuspjofferjan                    [  6];   //차선매도잔량         
	char fuspjbidjan                      [  6];   //차선매수잔량         
	char fuspjjoffer                      [  6];   //차차선매도호가       
	char fuspjjbid                        [  6];   //차차선매수호가       
	char fuspjjofferjan                   [  6];   //차차선매도잔량       
	char fuspjjbidjan                     [  6];   //차차선매수잔량       
	char fuspj4offer                      [  6];   //4차선매도호가        
	char fuspj4bid                        [  6];   //4차선매수호가        
	char fuspj4offerjan                   [  6];   //4차선매도잔량        
	char fuspj4bidjan                     [  6];   //4차선매수잔량        
	char fuspj5offer                      [  6];   //5차선매도호가        
	char fuspj5bid                        [  6];   //5차선매수호가        
	char fuspj5offerjan                   [  6];   //5차선매도잔량        
	char fuspj5bidjan                     [  6];   //5차선매수잔량        
	char fusptofferjan                    [  6];   //총매도잔량           
	char fusptbidjan                      [  6];   //총매수잔량           
	char fuspoffersu                      [  4];   //우선매도건수         
	char fuspjoffersu                     [  4];   //차선매도건수         
	char fuspjjoffersu                    [  4];   //차차선매도건수       
	char fuspj4offersu                    [  4];   //4차선매도건수        
	char fuspj5offersu                    [  4];   //5차선매도건수        
	char fusptoffersu                     [  5];   //총매도건수           
	char fuspbidsu                        [  4];   //우선매수건수         
	char fuspjbidsu                       [  4];   //차선매수건수         
	char fuspjjbidsu                      [  4];   //차차선매수건수       
	char fuspj4bidsu                      [  4];   //4차선매수건수        
	char fuspj5bidsu                      [  4];   //5차선매수건수        
	char fusptbidsu                       [  5];   //총매수건수           
} Tq1OutBlock;

typedef struct tagq1
{
	Tq1InBlock                        q1inblock                             ;  //입력 
	Tq1OutBlock                       q1outblock                            ;  //출력 
} Tq1;

typedef struct tagq2InBlock    //입력
{
	char fuspcode                         [  8];	char _fuspcode;                           //종목코드             
} Tq2InBlock;

typedef struct tagq2OutBlock    //출력
{
	char fuspcode                         [  8];	char _fuspcode;                           //종목코드             
	char fusphotime                       [  8];	char _fusphotime;                         //시간                 
	char fuspjgubun                       [  8];	char _fuspjgubun;                         //장운용               
	char fuspsign                         [  1];	char _fuspsign;                           //전일부호             
	char fuspchange                       [  9];	char _fuspchange;                         //전일대비             
	char fuspcurr                         [  6];	char _fuspcurr;                           //현재가               
	char fuspcurr1                        [  9];	char _fuspcurr1;                          //의제약정가(근월)     
	char fuspcurr2                        [  9];	char _fuspcurr2;                          //의제약정가(원월)     
	char fuspopen                         [  6];	char _fuspopen;                           //시가                 
	char fusphigh                         [  6];	char _fusphigh;                           //고가                 
	char fusplow                          [  6];	char _fusplow;                            //저가                 
	char fuspvol                          [  6];	char _fuspvol;                            //체결수량             
	char fuspvolall                       [  7];	char _fuspvolall;                         //누적체결수량         
	char fuspvalall                       [ 12];	char _fuspvalall;                         //누적거래대금         
	char fuspchrate                       [  5];	char _fuspchrate;                         //등락율               
	char fuspbp_jgubun                    [  1];	char _fuspbp_jgubun;                      //BP용장구분           
	char fuspoffer                        [  6];	char _fuspoffer;                          //우선매도호가         
	char fuspbid                          [  6];	char _fuspbid;                            //우선매수호가         
} Tq2OutBlock;

typedef struct tagq2
{
	Tq2InBlock                        q2inblock                             ;  //입력 
	Tq2OutBlock                       q2outblock                            ;  //출력 
} Tq2;

typedef struct tago1InBlock    //입력
{
	char opitem                           [  8];   //코드                 
} To1InBlock;

typedef struct tago1OutBlock    //출력
{
	char opitem                           [  8];   //코드                 
	char ophotime                         [  8];   //시간                 
	char opoffer                          [  9];   //매도우선호가         
	char opbid                            [  9];   //매수우선호가         
	char opofferjan                       [  7];   //매도우선잔량         
	char opbidjan                         [  7];   //매수우선잔량         
	char opjoffer                         [  9];   //차선매도호가         
	char opjbid                           [  9];   //차선매수호가         
	char opjofferjan                      [  7];   //차선매도잔량         
	char opjbidjan                        [  7];   //차선매수잔량         
	char opjjoffer                        [  9];   //차차선매도호가       
	char opjjbid                          [  9];   //차차선매수호가       
	char opjjofferjan                     [  7];   //차차선매도잔량       
	char opjjbidjan                       [  7];   //차차선매수잔량       
	char optofferjan                      [  7];   //총매도잔량           
	char optbidjan                        [  7];   //총매수잔량           
	char opj4offer                        [  9];   //4차선매도호가        
	char opj4bid                          [  9];   //4차선매수호가        
	char opj4offerjan                     [  7];   //4차선매도잔량        
	char opj4bidjan                       [  7];   //4차선매수잔량        
	char opj5offer                        [  9];   //5차선매도호가        
	char opj5bid                          [  9];   //5차선매수호가        
	char opj5offerjan                     [  7];   //5차선매도잔량        
	char opj5bidjan                       [  7];   //5차선매수잔량        
	char opoffersu                        [  4];   //우선매도건수         
	char opjoffersu                       [  4];   //차선매도건수         
	char opjjoffersu                      [  4];   //차차선매도건수       
	char opj4offersu                      [  4];   //4차선매도건수        
	char opj5offersu                      [  4];   //5차선매도건수        
	char optoffersu                       [  5];   //총매도건수           
	char opbidsu                          [  4];   //우선매수건수         
	char opjbidsu                         [  4];   //차선매수건수         
	char opjjbidsu                        [  4];   //차차선매수건수       
	char opj4bidsu                        [  4];   //4차선매수건수        
	char opj5bidsu                        [  4];   //5차선매수건수        
	char optbidsu                         [  5];   //총매수건수           
} To1OutBlock;

typedef struct tago1
{
	To1InBlock                        o1inblock                             ;  //입력 
	To1OutBlock                       o1outblock                            ;  //출력 
} To1;

typedef struct tago2InBlock    //입력
{
	char opitem                           [  8];	char _opitem;                             //종목코드             
} To2InBlock;

typedef struct tago2OutBlock    //출력
{
	char opitem                           [  8];	char _opitem;                             //종목코드             
	char opchetime                        [  8];	char _opchetime;                          //시간                 
	char opjgubun                         [  8];	char _opjgubun;                           //장운용               
	char opsign                           [  1];	char _opsign;                             //등락부호             
	char opchange                         [  9];	char _opchange;                           //등락폭               
	char opcurr                           [  9];	char _opcurr;                             //현재가               
	char opopen                           [  9];	char _opopen;                             //시가                 
	char ophigh                           [  9];	char _ophigh;                             //고가                 
	char oplow                            [  9];	char _oplow;                              //저가                 
	char opvol                            [  6];	char _opvol;                              //체결수량             
	char opvolallz8                       [  8];	char _opvolallz8;                         //누적체결수량         
	char opvalall                         [ 12];	char _opvalall;                           //누적거래대금         
	char opopenyak                        [  7];	char _opopenyak;                          //미결제약정수량       
	char opoffer                          [  9];	char _opoffer;                            //우선매도호가         
	char opbid                            [  9];	char _opbid;                              //우선매수호가         
	char opofferjan                       [  7];	char _opofferjan;                         //우선매도잔량         
	char opbidjan                         [  7];	char _opbidjan;                           //우선매수잔량         
	char opjoffer                         [  9];	char _opjoffer;                           //차선매도호가         
	char opjbid                           [  9];	char _opjbid;                             //차선매수호가         
	char opjofferjan                      [  7];	char _opjofferjan;                        //차선매도잔량         
	char opjbidjan                        [  7];	char _opjbidjan;                          //차선매수잔량         
	char opjjoffer                        [  9];	char _opjjoffer;                          //차차선매도호가       
	char opjjbid                          [  9];	char _opjjbid;                            //차차선매수호가       
	char opjjofferjan                     [  7];	char _opjjofferjan;                       //차차선매도잔량       
	char opjjbidjan                       [  7];	char _opjjbidjan;                         //차차선매수잔량       
	char optofferjan                      [  7];	char _optofferjan;                        //총매도잔량           
	char optbidjan                        [  7];	char _optbidjan;                          //총매수잔량           
	char opj4offer                        [  9];	char _opj4offer;                          //4차선매도호가        
	char opj4bid                          [  9];	char _opj4bid;                            //4차선매수호가        
	char opj4offerjan                     [  7];	char _opj4offerjan;                       //4차선매도잔량        
	char opj4bidjan                       [  7];	char _opj4bidjan;                         //4차선매수잔량        
	char opj5offer                        [  9];	char _opj5offer;                          //5차선매도호가        
	char opj5bid                          [  9];	char _opj5bid;                            //5차선매수호가        
	char opj5offerjan                     [  7];	char _opj5offerjan;                       //5차선매도잔량        
	char opj5bidjan                       [  7];	char _opj5bidjan;                         //5차선매수잔량        
	char opoffersu                        [  4];	char _opoffersu;                          //우선매도건수         
	char opjoffersu                       [  4];	char _opjoffersu;                         //차선매도건수         
	char opjjoffersu                      [  4];	char _opjjoffersu;                        //차차선매도건수       
	char opj4offersu                      [  4];	char _opj4offersu;                        //4차선매도건수        
	char opj5offersu                      [  4];	char _opj5offersu;                        //5차선매도건수        
	char optoffersu                       [  5];	char _optoffersu;                         //총매도건수           
	char opbidsu                          [  4];	char _opbidsu;                            //우선매수건수         
	char opjbidsu                         [  4];	char _opjbidsu;                           //차선매수건수         
	char opjjbidsu                        [  4];	char _opjjbidsu;                          //차차선매수건수       
	char opj4bidsu                        [  4];	char _opj4bidsu;                          //4차선매수건수        
	char opj5bidsu                        [  4];	char _opj5bidsu;                          //5차선매수건수        
	char optbidsu                         [  5];	char _optbidsu;                           //총매수건수           
	char opchrate                         [  5];	char _opchrate;                           //등락률               
	char opgrate                          [  9];	char _opgrate;                            //괴리도               
	char opgratio                         [  5];	char _opgratio;                           //괴리율               
	char oppreopenyak                     [  7];	char _oppreopenyak;                       //미결제약정전일       
	char opbp_jgubun                      [  1];	char _opbp_jgubun;                        //BP용장구분           
	char bulkvolz8                        [  8];	char _bulkvolz8;                          //혐의대량누적체결수량 
} To2OutBlock;

typedef struct tago2
{
	To2InBlock                        o2inblock                             ;  //입력 
	To2OutBlock                       o2outblock                            ;  //출력 
} To2;

typedef struct tago3InBlock    //입력
{
	char opitem                           [  8];   //종목코드             
} To3InBlock;

typedef struct tago3OutBlock    //출력
{
	char opitem                           [  8];   //종목코드             
	char optheorytime                     [  8];   //이론가시간           
	char optheoryprice                    [  9];   //옵션이론가           
	char opimpv                           [  5];   //내재변동성           
	char opdelta                          [  8];   //부호+델타            
	char opgmma                           [  8];   //부호+감마            
	char opvega                           [  8];   //부호+베가            
	char optheta                          [  8];   //부호+세타            
	char oprho                            [  8];   //부호+로              
	char opgrate                          [  9];   //괴리도               
	char opgratio                         [  5];   //괴리율               
} To3OutBlock;

typedef struct tago3
{
	To3InBlock                        o3inblock                             ;  //입력 
	To3OutBlock                       o3outblock                            ;  //출력 
} To3;

typedef struct tago4InBlock    //입력
{
	char opitem                           [  8];   //종목코드             
} To4InBlock;

typedef struct tago4OutBlock    //출력
{
	char opitem                           [  8];   //종목코드             
	char opchetime                        [  8];   //체결시간             
	char opopenyak                        [  7];   //미결제약정수량       
	char oppreopenyak                     [  7];   //전일미결제약정수량   
} To4OutBlock;

typedef struct tago4
{
	To4InBlock                        o4inblock                             ;  //입력 
	To4OutBlock                       o4outblock                            ;  //출력 
} To4;


typedef struct tagvHInBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} TvHInBlock;

typedef struct tagvHOutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char futime                           [  8];   //시간 HH:MM:SS        
	char offer                            [  7];   //매도호가             
	char bid                              [  7];   //매수호가             
	char offerjan                         [  7];   //매도잔량             
	char bidjan                           [  7];   //매수잔량             
	char S2offer                          [  7];   //차매도호가           
	char S2bid                            [  7];   //차매수호가           
	char S2offerjan                       [  7];   //차매도잔량           
	char S2bidjan                         [  7];   //차매수잔량           
	char S3offer                          [  7];   //차차매도호가         
	char S3bid                            [  7];   //차차매수호가         
	char S3offerjan                       [  7];   //차차매도잔량         
	char S3bidjan                         [  7];   //차차매수잔량         
	char S4offer                          [  7];   //4차매도호가          
	char S4bid                            [  7];   //4차매수호가          
	char S4offerjan                       [  7];   //4차매도잔량          
	char S4bidjan                         [  7];   //4차매수잔량          
	char S5offer                          [  7];   //5차매도호가          
	char S5bid                            [  7];   //5차매수호가          
	char S5offerjan                       [  7];   //5차매도잔량          
	char S5bidjan                         [  7];   //5차매수잔량          
	char S6offer                          [  7];   //6차매도호가          
	char S6bid                            [  7];   //6차매수호가          
	char S6offerjan                       [  7];   //6차매도잔량          
	char S6bidjan                         [  7];   //6차매수잔량          
	char S7offer                          [  7];   //7차매도호가          
	char S7bid                            [  7];   //7차매수호가          
	char S7offerjan                       [  7];   //7차매도잔량          
	char S7bidjan                         [  7];   //7차매수잔량          
	char S8offer                          [  7];   //8차매도호가          
	char S8bid                            [  7];   //8차매수호가          
	char S8offerjan                       [  7];   //8차매도잔량          
	char S8bidjan                         [  7];   //8차매수잔량          
	char S9offer                          [  7];   //9차매도호가          
	char S9bid                            [  7];   //9차매수호가          
	char S9offerjan                       [  7];   //9차매도잔량          
	char S9bidjan                         [  7];   //9차매수잔량          
	char S0offer                          [  7];   //10차매도호가         
	char S0bid                            [  7];   //10차매수호가         
	char S0offerjan                       [  7];   //10차매도잔량         
	char S0bidjan                         [  7];   //10차매수잔량         
	char offersu                          [  4];   //우 선 매도 건수              
	char bidsu                            [  4];   //우 선 매수 건수      
	char S2offersu                        [  4];   //차 선 매도 건수      
	char S2bidsu                          [  4];   //차 선 매수 건수      
	char S3offersu                        [  4];   //3차선 매도 건수      
	char S3bidsu                          [  4];   //3차선 매수 건수      
	char S4offersu                        [  4];   //4차선 매도 건수      
	char S4bidsu                          [  4];   //4차선 매수 건수      
	char S5offersu                        [  4];   //5차선 매도 건수      
	char S5bidsu                          [  4];   //5차선 매수 건수      
	char S6offersu                        [  4];   //6차선 매도 건수      
	char S6bidsu                          [  4];   //6차선 매수 건수      
	char S7offersu                        [  4];   //7차선 매도 건수      
	char S7bidsu                          [  4];   //7차선 매수 건수      
	char S8offersu                        [  4];   //8차선 매도 건수      
	char S8bidsu                          [  4];   //8차선 매수 건수      
	char S9offersu                        [  4];   //9차선 매도 건수      
	char S9bidsu                          [  4];   //9차선 매수 건수      
	char S0offersu                        [  4];   //10차선 매도 건수     
	char S0bidsu                          [  4];   //10차선 매수 건수     
	char tofferjan                        [  8];   //총매도호가 잔량      
	char tobidjan                         [  8];   //총매수 호가 잔량     
	char toffersu                         [  5];   //총 매도 건수         
	char tbidsu                           [  5];   //총 매수 건수         
} TvHOutBlock;

typedef struct tagvH
{
	TvHInBlock                        vhinblock                             ;  //입력 
	TvHOutBlock                       vhoutblock                            ;  //출력 
} TvH;



typedef struct tagvCInBlock    //입력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
} TvCInBlock;

typedef struct tagvCOutBlock    //출력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
	char futime                           [  8];	char _futime;                             //시간 HH:MM:SS        
	char jgubun                           [  8];	char _jgubun;                             //장운용               
	char fusign                           [  1];	char _fusign;                             //전일대비 부호        
	char fuchange                         [  7];	char _fuchange;                           //전일대비             
	char fucurr                           [  7];	char _fucurr;                             //현재가               
	char fuopen                           [  7];	char _fuopen;                             //시가                 
	char fuhigh                           [  7];	char _fuhigh;                             //고가                 
	char fulow                            [  7];	char _fulow;                              //저가                 
	char fuvol                            [  6];	char _fuvol;                              //체결수량             
	char fuvolall                         [  7];	char _fuvolall;                           //누적 체결수량        
	char fuvalall                         [ 12];	char _fuvalall;                           //누적거래대금         
	char openyak                          [  7];	char _openyak;                            //미결제약정수량       
	char jandatecnt                       [  3];	char _jandatecnt;                         //잔존일수             
	char offer                            [  7];	char _offer;                              //매도호가             
	char bid                              [  7];	char _bid;                                //매수호가             
	char offerjan                         [  7];	char _offerjan;                           //매도잔량             
	char bidjan                           [  7];	char _bidjan;                             //매수잔량             
	char S2offer                          [  7];	char _S2offer;                            //차매도호가           
	char S2bid                            [  7];	char _S2bid;                              //차매수호가           
	char S2offerjan                       [  7];	char _S2offerjan;                         //차매도잔량           
	char S2bidjan                         [  7];	char _S2bidjan;                           //차매수잔량           
	char S3offer                          [  7];	char _S3offer;                            //차차매도호가         
	char S3bid                            [  7];	char _S3bid;                              //차차매수호가         
	char S3offerjan                       [  7];	char _S3offerjan;                         //차차매도잔량         
	char S3bidjan                         [  7];	char _S3bidjan;                           //차차매수잔량         
	char S4offer                          [  7];	char _S4offer;                            //4차매도호가          
	char S4bid                            [  7];	char _S4bid;                              //4차매수호가          
	char S4offerjan                       [  7];	char _S4offerjan;                         //4차매도잔량          
	char S4bidjan                         [  7];	char _S4bidjan;                           //4차매수잔량          
	char S5offer                          [  7];	char _S5offer;                            //5차매도호가          
	char S5bid                            [  7];	char _S5bid;                              //5차매수호가          
	char S5offerjan                       [  7];	char _S5offerjan;                         //5차매도잔량          
	char S5bidjan                         [  7];	char _S5bidjan;                           //5차매수잔량          
	char S6offer                          [  7];	char _S6offer;                            //6차매도호가          
	char S6bid                            [  7];	char _S6bid;                              //6차매수호가          
	char S6offerjan                       [  7];	char _S6offerjan;                         //6차매도잔량          
	char S6bidjan                         [  7];	char _S6bidjan;                           //6차매수잔량          
	char S7offer                          [  7];	char _S7offer;                            //7차매도호가          
	char S7bid                            [  7];	char _S7bid;                              //7차매수호가          
	char S7offerjan                       [  7];	char _S7offerjan;                         //7차매도잔량          
	char S7bidjan                         [  7];	char _S7bidjan;                           //7차매수잔량          
	char S8offer                          [  7];	char _S8offer;                            //8차매도호가          
	char S8bid                            [  7];	char _S8bid;                              //8차매수호가          
	char S8offerjan                       [  7];	char _S8offerjan;                         //8차매도잔량          
	char S8bidjan                         [  7];	char _S8bidjan;                           //8차매수잔량          
	char S9offer                          [  7];	char _S9offer;                            //9차매도호가          
	char S9bid                            [  7];	char _S9bid;                              //9차매수호가          
	char S9offerjan                       [  7];	char _S9offerjan;                         //9차매도잔량          
	char S9bidjan                         [  7];	char _S9bidjan;                           //9차매수잔량          
	char S0offer                          [  7];	char _S0offer;                            //10차매도호가         
	char S0bid                            [  7];	char _S0bid;                              //10차매수호가         
	char S0offerjan                       [  7];	char _S0offerjan;                         //10차매도잔량         
	char S0bidjan                         [  7];	char _S0bidjan;                           //10차매수잔량         
	char offersu                          [  4];	char _offersu;                            //우 선 매도 건수      
	char bidsu                            [  4];	char _bidsu;                              //우 선 매수 건수      
	char S2offersu                        [  4];	char _S2offersu;                          //차 선 매도 건수      
	char S2bidsu                          [  4];	char _S2bidsu;                            //차 선 매수 건수      
	char S3offersu                        [  4];	char _S3offersu;                          //3차선 매도 건수      
	char S3bidsu                          [  4];	char _S3bidsu;                            //3차선 매수 건수      
	char S4offersu                        [  4];	char _S4offersu;                          //4차선 매도 건수      
	char S4bidsu                          [  4];	char _S4bidsu;                            //4차선 매수 건수      
	char S5offersu                        [  4];	char _S5offersu;                          //5차선 매도 건수      
	char S5bidsu                          [  4];	char _S5bidsu;                            //5차선 매수 건수      
	char S6offersu                        [  4];	char _S6offersu;                          //6차선 매도 건수      
	char S6bidsu                          [  4];	char _S6bidsu;                            //6차선 매수 건수      
	char S7offersu                        [  4];	char _S7offersu;                          //7차선 매도 건수      
	char S7bidsu                          [  4];	char _S7bidsu;                            //7차선 매수 건수      
	char S8offersu                        [  4];	char _S8offersu;                          //8차선 매도 건수      
	char S8bidsu                          [  4];	char _S8bidsu;                            //8차선 매수 건수      
	char S9offersu                        [  4];	char _S9offersu;                          //9차선 매도 건수      
	char S9bidsu                          [  4];	char _S9bidsu;                            //9차선 매수 건수      
	char S0offersu                        [  4];	char _S0offersu;                          //10차선 매도 건수     
	char S0bidsu                          [  4];	char _S0bidsu;                            //10차선 매수 건수     
	char tofferjan                        [  8];	char _tofferjan;                          //총매도호가 잔량      
	char tobidjan                         [  8];	char _tobidjan;                           //총매수 호가 잔량     
	char toffersu                         [  5];	char _toffersu;                           //총 매도 건수         
	char tbidsu                           [  5];	char _tbidsu;                             //총 매수 건수         
	char chrate                           [  5];	char _chrate;                             //등락률               
	char basis                            [  7];	char _basis;                              //베이시스             
	char grate                            [  7];	char _grate;                              //괴리도               
	char gratio                           [  6];	char _gratio;                             //괴리율               
	char preopenyak                       [  7];	char _preopenyak;                         //미결제약정전일비     
	char bp_jgubun                        [  1];	char _bp_jgubun;                          //BP용 장구분          
	char fspvolall                        [  7];	char _fspvolall;                          //스프레드 체결수량    
} TvCOutBlock;

typedef struct tagvC
{
	TvCInBlock                        vcinblock                             ;  //입력 
	TvCOutBlock                       vcoutblock                            ;  //출력 
} TvC;



typedef struct tagvVInBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} TvVInBlock;

typedef struct tagvVOutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char theoryprice                      [  7];   //선물 이론가          
	char theorytime                       [  8];   //이론가 시간          
	char grate                            [  7];   //괴리도               
	char gratio                           [  6];   //괴리율               
} TvVOutBlock;

typedef struct tagvV
{
	TvVInBlock                        vvinblock                             ;  //입력 
	TvVOutBlock                       vvoutblock                            ;  //출력 
} TvV;


typedef struct tagvMInBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} TvMInBlock;

typedef struct tagvMOutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char chetime                          [  8];   //체결시간             
	char openyak                          [  7];   //미결제약정수량       
	char preopenyak                       [  7];   //전일미결제약정수량   
} TvMOutBlock;

typedef struct tagvM
{
	TvMInBlock                        vminblock                             ;  //입력 
	TvMOutBlock                       vmoutblock                            ;  //출력 
} TvM;


typedef struct tagv7InBlock    //입력
{
	char fspitem                          [  8];   //스프레드종목코드     
} Tv7InBlock;

typedef struct tagv7OutBlock    //출력
{
	char fspitem                          [  8];   //스프레드종목코드     
	char fsptime                          [  8];   //시간 HH:MM:SS        
	char offer                            [  8];   //매도호가             
	char bid                              [  8];   //매수호가             
	char offerjan                         [  7];   //매도잔량             
	char bidjan                           [  7];   //매수잔량             
	char S2offer                          [  8];   //차매도호가           
	char S2bid                            [  8];   //차매수호가           
	char S2offerjan                       [  7];   //차매도잔량           
	char S2bidjan                         [  7];   //차매수잔량           
	char S3offer                          [  8];   //차차매도호가         
	char S3bid                            [  8];   //차차매수호가         
	char S3offerjan                       [  7];   //차차매도잔량         
	char S3bidjan                         [  7];   //차차매수잔량         
	char S4offer                          [  8];   //4차매도호가          
	char S4bid                            [  8];   //4차매수호가          
	char S4offerjan                       [  7];   //4차매도잔량          
	char S4bidjan                         [  7];   //4차매수잔량          
	char S5offer                          [  8];   //5차매도호가          
	char S5bid                            [  8];   //5차매수호가          
	char S5offerjan                       [  7];   //5차매도잔량          
	char S5bidjan                         [  7];   //5차매수잔량          
	char S6offer                          [  8];   //6차매도호가          
	char S6bid                            [  8];   //6차매수호가          
	char S6offerjan                       [  7];   //6차매도잔량          
	char S6bidjan                         [  7];   //6차매수잔량          
	char S7offer                          [  8];   //7차매도호가          
	char S7bid                            [  8];   //7차매수호가          
	char S7offerjan                       [  7];   //7차매도잔량          
	char S7bidjan                         [  7];   //7차매수잔량          
	char S8offer                          [  8];   //8차매도호가          
	char S8bid                            [  8];   //8차매수호가          
	char S8offerjan                       [  7];   //8차매도잔량          
	char S8bidjan                         [  7];   //8차매수잔량          
	char S9offer                          [  8];   //9차매도호가          
	char S9bid                            [  8];   //9차매수호가          
	char S9offerjan                       [  7];   //9차매도잔량          
	char S9bidjan                         [  7];   //9차매수잔량          
	char S0offer                          [  8];   //10차매도호가         
	char S0bid                            [  8];   //10차매수호가         
	char S0offerjan                       [  7];   //10차매도잔량         
	char S0bidjan                         [  7];   //10차매수잔량         
	char offersu                          [  4];   //우 선 매도 건수      
	char bidsu                            [  4];   //우 선 매수 건수      
	char S2offersu                        [  4];   //차 선 매도 건수      
	char S2bidsu                          [  4];   //차 선 매수 건수      
	char S3offersu                        [  4];   //3차선 매도 건수      
	char S3bidsu                          [  4];   //3차선 매수 건수      
	char S4offersu                        [  4];   //4차선 매도 건수      
	char S4bidsu                          [  4];   //4차선 매수 건수      
	char S5offersu                        [  4];   //5차선 매도 건수      
	char S5bidsu                          [  4];   //5차선 매수 건수      
	char S6offersu                        [  4];   //6차선 매도 건수      
	char S6bidsu                          [  4];   //6차선 매수 건수      
	char S7offersu                        [  4];   //7차선 매도 건수      
	char S7bidsu                          [  4];   //7차선 매수 건수      
	char S8offersu                        [  4];   //8차선 매도 건수      
	char S8bidsu                          [  4];   //8차선 매수 건수      
	char S9offersu                        [  4];   //9차선 매도 건수      
	char S9bidsu                          [  4];   //9차선 매수 건수      
	char S0offersu                        [  4];   //10차선 매도 건수     
	char S0bidsu                          [  4];   //10차선 매수 건수     
	char tofferjan                        [  8];   //총매도호가 잔량      
	char tobidjan                         [  8];   //총매수 호가 잔량     
	char toffersu                         [  5];   //총 매도 건수         
	char tbidsu                           [  5];   //총 매수 건수         
} Tv7OutBlock;

typedef struct tagv7
{
	Tv7InBlock                        v7inblock                             ;  //입력 
	Tv7OutBlock                       v7outblock                            ;  //출력 
} Tv7;



typedef struct tagv8InBlock    //입력
{
	char fspitem                          [  8];	char _fspitem;                            //스프레드종목코드     
} Tv8InBlock;

typedef struct tagv8OutBlock    //출력
{
	char fspitem                          [  8];	char _fspitem;                            //스프레드종목코드     
	char fsptime                          [  8];	char _fsptime;                            //시간 HH:MM:SS        
	char jgubun                           [  8];	char _jgubun;                             //장운용               
	char fspsign                          [  1];	char _fspsign;                            //전일대비 부호        
	char fspchange                        [  7];	char _fspchange;                          //전일대비             
	char fspcurr                          [  8];	char _fspcurr;                            //현재가               
	char fspcurr1                         [  7];	char _fspcurr1;                           //의제약정가-근월물    
	char fspcurr2                         [  7];	char _fspcurr2;                           //의제약정가-원월물    
	char fspopen                          [  8];	char _fspopen;                            //시가                 
	char fsphigh                          [  8];	char _fsphigh;                            //고가                 
	char fsplow                           [  8];	char _fsplow;                             //저가                 
	char fspvol                           [  6];	char _fspvol;                             //체결수량             
	char fspvolall                        [  7];	char _fspvolall;                          //누적 체결수량        
	char fspvalall                        [ 12];	char _fspvalall;                          //누적거래대금         
	char offer                            [  8];	char _offer;                              //매도호가             
	char bid                              [  8];	char _bid;                                //매수호가             
	char offerjan                         [  7];	char _offerjan;                           //매도잔량             
	char bidjan                           [  7];	char _bidjan;                             //매수잔량             
	char S2offer                          [  8];	char _S2offer;                            //차매도호가           
	char S2bid                            [  8];	char _S2bid;                              //차매수호가           
	char S2offerjan                       [  7];	char _S2offerjan;                         //차매도잔량           
	char S2bidjan                         [  7];	char _S2bidjan;                           //차매수잔량           
	char S3offer                          [  8];	char _S3offer;                            //차차매도호가         
	char S3bid                            [  8];	char _S3bid;                              //차차매수호가         
	char S3offerjan                       [  7];	char _S3offerjan;                         //차차매도잔량         
	char S3bidjan                         [  7];	char _S3bidjan;                           //차차매수잔량         
	char S4offer                          [  8];	char _S4offer;                            //4차매도호가          
	char S4bid                            [  8];	char _S4bid;                              //4차매수호가          
	char S4offerjan                       [  7];	char _S4offerjan;                         //4차매도잔량          
	char S4bidjan                         [  7];	char _S4bidjan;                           //4차매수잔량          
	char S5offer                          [  8];	char _S5offer;                            //5차매도호가          
	char S5bid                            [  8];	char _S5bid;                              //5차매수호가          
	char S5offerjan                       [  7];	char _S5offerjan;                         //5차매도잔량          
	char S5bidjan                         [  7];	char _S5bidjan;                           //5차매수잔량          
	char S6offer                          [  8];	char _S6offer;                            //6차매도호가          
	char S6bid                            [  8];	char _S6bid;                              //6차매수호가          
	char S6offerjan                       [  7];	char _S6offerjan;                         //6차매도잔량          
	char S6bidjan                         [  7];	char _S6bidjan;                           //6차매수잔량          
	char S7offer                          [  8];	char _S7offer;                            //7차매도호가          
	char S7bid                            [  8];	char _S7bid;                              //7차매수호가          
	char S7offerjan                       [  7];	char _S7offerjan;                         //7차매도잔량          
	char S7bidjan                         [  7];	char _S7bidjan;                           //7차매수잔량          
	char S8offer                          [  8];	char _S8offer;                            //8차매도호가          
	char S8bid                            [  8];	char _S8bid;                              //8차매수호가          
	char S8offerjan                       [  7];	char _S8offerjan;                         //8차매도잔량          
	char S8bidjan                         [  7];	char _S8bidjan;                           //8차매수잔량          
	char S9offer                          [  8];	char _S9offer;                            //9차매도호가          
	char S9bid                            [  8];	char _S9bid;                              //9차매수호가          
	char S9offerjan                       [  7];	char _S9offerjan;                         //9차매도잔량          
	char S9bidjan                         [  7];	char _S9bidjan;                           //9차매수잔량          
	char S0offer                          [  8];	char _S0offer;                            //10차매도호가         
	char S0bid                            [  8];	char _S0bid;                              //10차매수호가         
	char S0offerjan                       [  7];	char _S0offerjan;                         //10차매도잔량         
	char S0bidjan                         [  7];	char _S0bidjan;                           //10차매수잔량         
	char offersu                          [  4];	char _offersu;                            //우 선 매도 건수      
	char bidsu                            [  4];	char _bidsu;                              //우 선 매수 건수      
	char S2offersu                        [  4];	char _S2offersu;                          //차 선 매도 건수      
	char S2bidsu                          [  4];	char _S2bidsu;                            //차 선 매수 건수      
	char S3offersu                        [  4];	char _S3offersu;                          //3차선 매도 건수      
	char S3bidsu                          [  4];	char _S3bidsu;                            //3차선 매수 건수      
	char S4offersu                        [  4];	char _S4offersu;                          //4차선 매도 건수      
	char S4bidsu                          [  4];	char _S4bidsu;                            //4차선 매수 건수      
	char S5offersu                        [  4];	char _S5offersu;                          //5차선 매도 건수      
	char S5bidsu                          [  4];	char _S5bidsu;                            //5차선 매수 건수      
	char S6offersu                        [  4];	char _S6offersu;                          //6차선 매도 건수      
	char S6bidsu                          [  4];	char _S6bidsu;                            //6차선 매수 건수      
	char S7offersu                        [  4];	char _S7offersu;                          //7차선 매도 건수      
	char S7bidsu                          [  4];	char _S7bidsu;                            //7차선 매수 건수      
	char S8offersu                        [  4];	char _S8offersu;                          //8차선 매도 건수      
	char S8bidsu                          [  4];	char _S8bidsu;                            //8차선 매수 건수      
	char S9offersu                        [  4];	char _S9offersu;                          //9차선 매도 건수      
	char S9bidsu                          [  4];	char _S9bidsu;                            //9차선 매수 건수      
	char S0offersu                        [  4];	char _S0offersu;                          //10차선 매도 건수     
	char S0bidsu                          [  4];	char _S0bidsu;                            //10차선 매수 건수     
	char tofferjan                        [  8];	char _tofferjan;                          //총매도호가 잔량      
	char tobidjan                         [  8];	char _tobidjan;                           //총매수 호가 잔량     
	char toffersu                         [  5];	char _toffersu;                           //총 매도 건수         
	char tbidsu                           [  5];	char _tbidsu;                             //총 매수 건수         
	char chrate                           [  5];	char _chrate;                             //등락률               
	char bp_jgubun                        [  1];	char _bp_jgubun;                          //BP용 장구분          
} Tv8OutBlock;

typedef struct tagv8
{
	Tv8InBlock                        v8inblock                             ;  //입력 
	Tv8OutBlock                       v8outblock                            ;  //출력 
} Tv8;



typedef struct tageCInBlock    //입력
{
	char code                             [  6];	char _code;                               //종목코드             
} TeCInBlock;

typedef struct tageCOutBlock    //출력
{
	char code                             [  6];	char _code;                               //단축종목코드         
	char time                             [  8];	char _time;                               //시간(HH:MM:SS)       
	char price                            [  7];	char _price;                              //현재가               
	char sign                             [  1];	char _sign;                               //등락부호             
	char change                           [  6];	char _change;                             //등락폭               
	char chrate                           [  5];	char _chrate;                             //등락률               
	char open                             [  7];	char _open;                               //시가                 
	char high                             [  7];	char _high;                               //고가                 
	char low                              [  7];	char _low;                                //저가                 
	char offer                            [  7];	char _offer;                              //매도호가             
	char bid                              [  7];	char _bid;                                //매수호가             
	char volume                           [  9];	char _volume;                             //누적거래량           
	char volrate                          [  6];	char _volrate;                            //거래량 전일비        
	char movolume                         [  8];	char _movolume;                           //변동거래량           
	char value                            [  9];	char _value;                              //거래대금 백만원      
	char janggubun                        [  1];	char _janggubun;                          //장구분               
	char cbgubun                          [  1];	char _cbgubun;                            //CB구분               
	char stop                             [  1];	char _stop;                               //STOP                 
	char grate                            [  6];	char _grate;                              //괴리도 9(6)          
	char gratio                           [  8];	char _gratio;                             //괴리율S9(5)V9(2)     
	char lphold                           [  9];	char _lphold;                             //LP보유수량           
	char lprate                           [  5];	char _lprate;                             //LP보유률             
} TeCOutBlock;

typedef struct tageC
{
	TeCInBlock                        ecinblock                             ;  //입력 
	TeCOutBlock                       ecoutblock                            ;  //출력 
} TeC;


typedef struct tageHInBlock    //입력
{
	char code                             [  6];   //종목코드             
} TeHInBlock;

typedef struct tageHOutBlock    //출력
{
	char code                             [  6];   //단축코드             
	char time                             [  8];   //시간                 
	char S1_off                           [  7];   //매도호가             
	char S1_bid                           [  7];   //매수호가             
	char S1_offrem                        [  9];   //매도호가 잔량        
	char S1_bidrem                        [  9];   //매수호가 잔량        
	char S2_off                           [  7];   //2차매도호가          
	char S2_bid                           [  7];   //2차매수호가          
	char S2_offrem                        [  9];   //2차매도호가 잔량     
	char S2_bidrem                        [  9];   //2차매수호가 잔량     
	char S3_off                           [  7];   //3차매도호가          
	char S3_bid                           [  7];   //3차매수호가          
	char S3_offrem                        [  9];   //3차매도호가 잔량     
	char S3_bidrem                        [  9];   //3차매수호가 잔량     
	char S4_off                           [  7];   //4차매도호가          
	char S4_bid                           [  7];   //4차매수호가          
	char S4_offrem                        [  9];   //4차매도호가 잔량     
	char S4_bidrem                        [  9];   //4차매수호가 잔량     
	char S5_off                           [  7];   //5차매도호가          
	char S5_bid                           [  7];   //5차매수호가          
	char S5_offrem                        [  9];   //5차매도호가 잔량     
	char S5_bidrem                        [  9];   //5차매수호가 잔량     
	char S6_off                           [  7];   //6차매도호가          
	char S6_bid                           [  7];   //6차매수호가          
	char S6_offrem                        [  9];   //6차매도호가 잔량     
	char S6_bidrem                        [  9];   //6차매수호가 잔량     
	char S7_off                           [  7];   //7차매도호가          
	char S7_bid                           [  7];   //7차매수호가          
	char S7_offrem                        [  9];   //7차매도호가 잔량     
	char S7_bidrem                        [  9];   //7차매수호가 잔량     
	char S8_off                           [  7];   //8차매도호가          
	char S8_bid                           [  7];   //8차매수호가          
	char S8_offrem                        [  9];   //8차매도호가 잔량     
	char S8_bidrem                        [  9];   //8차매수호가 잔량     
	char S9_off                           [  7];   //9차매도호가          
	char S9_bid                           [  7];   //9차매수호가          
	char S9_offrem                        [  9];   //9차매도호가 잔량     
	char S9_bidrem                        [  9];   //9차매수호가 잔량     
	char S10_off                          [  7];   //10차매도호가         
	char S10_bid                          [  7];   //10차매수호가         
	char S10_offrem                       [  9];   //10차매도호가 잔량    
	char S10_bidrem                       [  9];   //10차매수호가 잔량    
	char T_offrem                         [  9];   //총매도호가 잔량      
	char T_bidrem                         [  9];   //총매수호가 잔량      
	char dongsi                           [  1];   //동시구분             
	char eqprice                          [  7];   //동시호가시예상체결가 
	char sign                             [  1];   //등락부호             
	char change                           [  6];   //등락폭               
	char chrate                           [  5];   //등락률               
	char eqvol                            [  9];   //동시호가시예상체결수량 
	char S1_lpoffrem                      [  9];   //1차LP매도호가 잔량   
	char S1_lpbidrem                      [  9];   //1차LP매수호가 잔량   
	char S2_lpoffrem                      [  9];   //2차LP매도호가 잔량   
	char S2_lpbidrem                      [  9];   //2차LP매수호가 잔량   
	char S3_lpoffrem                      [  9];   //3차LP매도호가 잔량   
	char S3_lpbidrem                      [  9];   //3차LP매수호가 잔량   
	char S4_lpoffrem                      [  9];   //4차LP매도호가 잔량   
	char S4_lpbidrem                      [  9];   //4차LP매수호가 잔량   
	char S5_lpoffrem                      [  9];   //5차LP매도호가 잔량   
	char S5_lpbidrem                      [  9];   //5차LP매수호가 잔량   
	char S6_lpoffrem                      [  9];   //6차LP매도호가 잔량   
	char S6_lpbidrem                      [  9];   //6차LP매수호가 잔량   
	char S7_lpoffrem                      [  9];   //7차LP매도호가 잔량   
	char S7_lpbidrem                      [  9];   //7차LP매수호가 잔량   
	char S8_lpoffrem                      [  9];   //8차LP매도호가 잔량   
	char S8_lpbidrem                      [  9];   //8차LP매수호가 잔량   
	char S9_lpoffrem                      [  9];   //9차LP매도호가 잔량   
	char S9_lpbidrem                      [  9];   //9차LP매수호가 잔량   
	char S10_lpoffrem                     [  9];   //10차LP매도호가 잔량  
	char S10_lpbidrem                     [  9];   //10차LP매수호가 잔량  
} TeHOutBlock;

typedef struct tageH
{
	TeHInBlock                        ehinblock                             ;  //입력 
	TeHOutBlock                       ehoutblock                            ;  //출력 
} TeH;


typedef struct tageVInBlock    //입력
{
	char code                             [  6];   //종목코드             
} TeVInBlock;

typedef struct tageVOutBlock    //출력
{
	char code                             [  6];   //종목코드             
	char theorytime                       [  8];   //이론가시간           
	char theoryprice                      [  7];   //이론가               
	char impv                             [ 10];   //내재변동성           
	char delta                            [  9];   //부호+델타            
	char gmma                             [  9];   //부호+감마            
	char vega                             [  9];   //부호+베가            
	char theta                            [  9];   //부호+세타            
	char rho                              [  9];   //부호+로              
	char grate                            [  6];   //괴리도               
	char gratio                           [  8];   //괴리율               
} TeVOutBlock;

typedef struct tageV
{
	TeVInBlock                        evinblock                             ;  //입력 
	TeVOutBlock                       evoutblock                            ;  //출력 
} TeV;


typedef struct tageLInBlock    //입력
{
	char code                             [  6];   //종목코드             
} TeLInBlock;

typedef struct tageLOutBlock    //출력
{
	char code                             [  6];   //종목코드             
	char jipyotime                        [  8];   //투자지표시간         
	char parity                           [  8];   //패리티               
	char egearing                         [  8];   //E기어링              
	char gearingrate                      [  8];   //기어링비율           
	char profitrate                       [  8];   //손익분기율           
	char basepoint                        [  8];   //자본지지점           
	char filler                           [  6];   //FILLER               
} TeLOutBlock;

typedef struct tageL
{
	TeLInBlock                        elinblock                             ;  //입력 
	TeLOutBlock                       eloutblock                            ;  //출력 
} TeL;


typedef struct tageTInBlock    //입력
{
	char code                             [  6];	char _code;                               //종목코드             
} TeTInBlock;

typedef struct tageTOutBlock    //출력
{
	char code                             [  6];	char _code;                               //종목코드             
	char time                             [  8];	char _time;                               //시간                 
	char off_trano1                       [  4];	char _off_trano1;                         //매도회원사코드1      
	char off_tra1                         [  6];	char _off_tra1;                           //매도회원사단이름1    
	char N_off_tra1                       [ 20];	char _N_off_tra1;                         //매도회원사장이름1    
	char N_otraflag1                      [  1];	char _N_otraflag1;                        //매도회원사외구분1    
	char N_offvolume1                     [  9];	char _N_offvolume1;                       //매도거래량1          
	char N_offvolcha1                     [  9];	char _N_offvolcha1;                       //직전매도차1          	
	char bid_trano1                       [  4];	char _bid_trano1;                         //매수회원사코드1      
	char bid_tra1                         [  6];	char _bid_tra1;                           //매수회원사단이름1    
	char N_bid_tra1                       [ 20];	char _N_bid_tra1;                         //매수회원사장이름1    
	char N_btraflag1                      [  1];	char _N_btraflag1;                        //매수회원사외구분1    
	char N_bidvolume1                     [  9];	char _N_bidvolume1;                       //매수거래량1          
	char N_bidvolcha1                     [  9];	char _N_bidvolcha1;                       //직전매수차1          
	char off_trano2                       [  4];	char _off_trano2;                         //매도회원사코드2      
	char off_tra2                         [  6];	char _off_tra2;                           //매도회원사단이름2    
	char N_off_tra2                       [ 20];	char _N_off_tra2;                         //매도회원사장이름2    
	char N_otraflag2                      [  1];	char _N_otraflag2;                        //매도회원사외구분2    
	char N_offvolume2                     [  9];	char _N_offvolume2;                       //매도거래량2          
	char N_offvolcha2                     [  9];	char _N_offvolcha2;                       //직전매도차2          
	char bid_trano2                       [  4];	char _bid_trano2;                         //매수회원사코드2      
	char bid_tra2                         [  6];	char _bid_tra2;                           //매수회원사단이름2    
	char N_bid_tra2                       [ 20];	char _N_bid_tra2;                         //매수회원사장이름2    
	char N_btraflag2                      [  1];	char _N_btraflag2;                        //매수회원사외구분2    
	char N_bidvolume2                     [  9];	char _N_bidvolume2;                       //매수거래량2          
	char N_bidvolcha2                     [  9];	char _N_bidvolcha2;                       //직전매수차2          
	char off_trano3                       [  4];	char _off_trano3;                         //매도회원사코드3      
	char off_tra3                         [  6];	char _off_tra3;                           //매도회원사단이름3    
	char N_off_tra3                       [ 20];	char _N_off_tra3;                         //매도회원사장이름3    
	char N_otraflag3                      [  1];	char _N_otraflag3;                        //매도회원사외구분3    
	char N_offvolume3                     [  9];	char _N_offvolume3;                       //매도거래량3          
	char N_offvolcha3                     [  9];	char _N_offvolcha3;                       //직전매도차3          
	char bid_trano3                       [  4];	char _bid_trano3;                         //매수회원사코드3      
	char bid_tra3                         [  6];	char _bid_tra3;                           //매수회원사단이름3    
	char N_bid_tra3                       [ 20];	char _N_bid_tra3;                         //매수회원사장이름3    
	char N_btraflag3                      [  1];	char _N_btraflag3;                        //매수회원사외구분3    
	char N_bidvolume3                     [  9];	char _N_bidvolume3;                       //매수거래량3          
	char N_bidvolcha3                     [  9];	char _N_bidvolcha3;                       //직전매수차3          
	char off_trano4                       [  4];	char _off_trano4;                         //매도회원사코드4      
	char off_tra4                         [  6];	char _off_tra4;                           //매도회원사단이름4    
	char N_off_tra4                       [ 20];	char _N_off_tra4;                         //매도회원사장이름4    
	char N_otraflag4                      [  1];	char _N_otraflag4;                        //매도회원사외구분4    
	char N_offvolume4                     [  9];	char _N_offvolume4;                       //매도거래량4          
	char N_offvolcha4                     [  9];	char _N_offvolcha4;                       //직전매도차4          
	char bid_trano4                       [  4];	char _bid_trano4;                         //매수회원사코드4      
	char bid_tra4                         [  6];	char _bid_tra4;                           //매수회원사단이름4    
	char N_bid_tra4                       [ 20];	char _N_bid_tra4;                         //매수회원사장이름4    
	char N_btraflag4                      [  1];	char _N_btraflag4;                        //매수회원사외구분4    
	char N_bidvolume4                     [  9];	char _N_bidvolume4;                       //매수거래량4          
	char N_bidvolcha4                     [  9];	char _N_bidvolcha4;                       //직전매수차4          
	char off_trano5                       [  4];	char _off_trano5;                         //매도회원사코드5      
	char off_tra5                         [  6];	char _off_tra5;                           //매도회원사단이름5    
	char N_off_tra5                       [ 20];	char _N_off_tra5;                         //매도회원사장이름5    
	char N_otraflag5                      [  1];	char _N_otraflag5;                        //매도회원사외구분5    
	char N_offvolume5                     [  9];	char _N_offvolume5;                       //매도거래량5          
	char N_offvolcha5                     [  9];	char _N_offvolcha5;                       //직전매도차5          
	char bid_trano5                       [  4];	char _bid_trano5;                         //매수회원사코드5      
	char bid_tra5                         [  6];	char _bid_tra5;                           //매수회원사단이름5    
	char N_bid_tra5                       [ 20];	char _N_bid_tra5;                         //매수회원사장이름5    
	char N_btraflag5                      [  1];	char _N_btraflag5;                        //매수회원사외구분5    
	char N_bidvolume5                     [  9];	char _N_bidvolume5;                       //매수거래량5          
	char N_bidvolcha5                     [  9];	char _N_bidvolcha5;                       //직전매수차5          
	char N_offvolall                      [  9];	char _N_offvolall;                        //외국계회원사매도합   
	char N_offvolcha                      [  9];	char _N_offvolcha;                        //외국계직전매도차     
	char N_bidvolall                      [  9];	char _N_bidvolall;                        //외국계회원사매수합   
	char N_bidvolcha                      [  9];	char _N_bidvolcha;                        //외국계직전매수차     
	char N_soonmaesu                      [  9];	char _N_soonmaesu;                        //외국계회원순매수     
	char N_soonmaecha                     [  9];	char _N_soonmaecha;                       //외국계직전순매수차   
	char N_alloffvol                      [  9];	char _N_alloffvol;                        //매도전체합           
	char N_allbidvol                      [  9];	char _N_allbidvol;                        //매수전체합           
	char hname                            [ 13];	char _hname;                              //종목명               
	char kpgubun                          [  1];	char _kpgubun;                            //시장구분             
} TeTOutBlock;

typedef struct tageT
{
	TeTInBlock                        etinblock                             ;  //입력 
	TeTOutBlock                       etoutblock                            ;  //출력 
} TeT;


typedef struct tagfEInBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} TfEInBlock;

typedef struct tagfEOutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char time                             [  8];   //시간                 
	char dongsi                           [  1];   //동시호가구분         
	char eqsign                           [  1];   //예상등락부호         
	char eqprice                          [  9];   //예상체결가           
	char eqchange                         [  9];   //예상등락폭           
	char eqchrate                         [  5];   //예상등락률           
	char eqvolume                         [  9];   //예상체결수량                //파생시장제도개선(2024.03.13)
} TfEOutBlock;

typedef struct tagfE
{
	TfEInBlock                        feinblock                             ;  //입력 
	TfEOutBlock                       feoutblock                            ;  //출력 
} TfE;

typedef struct tagoEInBlock    //입력
{
	char opitem                           [  8];   //종목코드             
} ToEInBlock;

typedef struct tagoEOutBlock    //출력
{
	char opitem                           [  8];   //종목코드             
	char time                             [  8];   //시간                 
	char dongsi                           [  1];   //동시호가구분         
	char eqsign                           [  1];   //예상등락부호         
	char eqprice                          [  9];   //예상체결가           
	char eqchange                         [  9];   //예상등락폭           
	char eqchrate                         [  5];   //예상등락률           
	char eqvolume                         [  9];   //예상체결수량                //파생시장제도개선(2024.03.13)
} ToEOutBlock;

typedef struct tagoE
{
	ToEInBlock                        oeinblock                             ;  //입력 
	ToEOutBlock                       oeoutblock                            ;  //출력 
} ToE;

typedef struct tagvEInBlock    //입력
{
	char expcode                          [  8];   //종목코드             
} TvEInBlock;

typedef struct tagvEOutBlock    //출력
{
	char expcode                          [  8];   //종목코드             
	char time                             [  8];   //시간                 
	char dongsi                           [  1];   //동시호가구분         
	char eqsign                           [  1];   //예상등락부호         
	char eqprice                          [  7];   //예상체결가           
	char eqchange                         [  7];   //예상등락폭           
	char eqchrate                         [  5];   //예상등락률           
} TvEOutBlock;

typedef struct tagvE
{
	TvEInBlock                        veinblock                             ;  //입력 
	TvEOutBlock                       veoutblock                            ;  //출력 
} TvE;


typedef struct tagf7InBlock    //입력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
} Tf7InBlock;

typedef struct tagf7OutBlock    //출력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
	char futime                           [  8];	char _futime;                             //시간                 
	char exlmtstep                        [  1];	char _exlmtstep;                          //가격확대예정단계     
	char exlmtgb                          [  1];	char _exlmtgb;                            //가격확대예정 구분    
	char uplmtgb                          [  1];	char _uplmtgb;                            //가격제한확대상한단계 
	char dnlmtgb                          [  1];	char _dnlmtgb;                            //가격제한확대하한단계 
	char uplmtprice                       [  9];	char _uplmtprice;                         //적용된 단계 상한가   
	char dnlmtprice                       [  9];	char _dnlmtprice;                         //적용된 단계 하한가   
} Tf7OutBlock;

typedef struct tago7InBlock    //입력
{
	char opitem                           [  8];	char _opitem;                             //종목코드             
} To7InBlock;

typedef struct tago7OutBlock    //출력
{
	char opitem                           [  8];	char _opitem;                             //종목코드             
	char optime                           [  8];	char _optime;                             //시간                 
	char uplmtgb                          [  1];	char _uplmtgb;                            //가격제한확대상한단계 
	char dnlmtgb                          [  1];	char _dnlmtgb;                            //가격제한확대하한단계 
	char uplmtprice                       [  9];	char _uplmtprice;                         //적용된 단계 상한가   
	char dnlmtprice                       [  9];	char _dnlmtprice;                         //적용된 단계 하한가   
} To7OutBlock;

typedef struct tago7
{
	To7InBlock                        o7inblock                             ;  //입력 
	To7OutBlock                       o7outblock                            ;  //출력 
} To7;

typedef struct tagvIInBlock    //입력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
} TvIInBlock;

typedef struct tagvIOutBlock    //출력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
	char futime                           [  8];	char _futime;                             //시간                 
	char exlmtstep                        [  1];	char _exlmtstep;                          //가격확대예정단계     
	char exlmtgb                          [  1];	char _exlmtgb;                            //가격확대예정 구분    
	char uplmtgb                          [  1];	char _uplmtgb;                            //가격제한확대상한단계 
	char dnlmtgb                          [  1];	char _dnlmtgb;                            //가격제한확대하한단계 
	char uplmtprice                       [  7];	char _uplmtprice;                         //적용된 단계 상한가   
	char dnlmtprice                       [  7];	char _dnlmtprice;                         //적용된 단계 하한가   
} TvIOutBlock;

typedef struct tagvI
{
	TvIInBlock                        viinblock                             ;  //입력 
	TvIOutBlock                       vioutblock                            ;  //출력 
} TvI;


typedef struct tagu1InBlock    //입력
{
	char jisucode                         [  2];	char _jisucode;                           //업종코드             
} Tu1InBlock;

typedef struct tagu1OutBlock    //출력
{
	char jisucode                         [  2];	char _jisucode;                           //업종코드             
	char jisutime                         [  8];	char _jisutime;                           //시간                 
	char jisu                             [  8];	char _jisu;                               //지수                 
	char jisusign                         [  1];	char _jisusign;                           //등락부호             
	char jisuchange                       [  8];	char _jisuchange;                         //등락폭               
	char jisuvolume                       [  8];	char _jisuvolume;                         //거래량               
	char jisuvalue                        [  8];	char _jisuvalue;                          //거래대금             
	char jisuopen                         [  8];	char _jisuopen;                           //시가지수             
	char jisuhigh                         [  8];	char _jisuhigh;                           //고가지수             
	char jisuhightime                     [  8];	char _jisuhightime;                       //고가시간             
	char jisulow                          [  8];	char _jisulow;                            //저가지수             
	char jisulowtime                      [  8];	char _jisulowtime;                        //저가시간             
	char jisuchrate                       [  5];	char _jisuchrate;                         //지수등락률           
	char jisubrkvol                       [  5];	char _jisubrkvol;                         //거래비중             
} Tu1OutBlock;

typedef struct tagu1
{
	Tu1InBlock                        u1inblock                             ;  //입력 
	Tu1OutBlock                       u1outblock                            ;  //출력 
} Tu1;


typedef struct tagk1InBlock    //입력
{
	char jisukcode                        [  2];	char _jisukcode;                          //업종코드             
} Tk1InBlock;

typedef struct tagk1OutBlock    //출력
{
	char jisukcode                        [  2];	char _jisukcode;                          //업종코드             
	char jisuktime                        [  8];	char _jisuktime;                          //시간                 
	char jisuk                            [  8];	char _jisuk;                              //지수                 
	char jisuksign                        [  1];	char _jisuksign;                          //등락부호             
	char jisukchange                      [  8];	char _jisukchange;                        //등락폭               
	char jisukvolume                      [  8];	char _jisukvolume;                        //거래량               
	char jisukvalue                       [  8];	char _jisukvalue;                         //거래대금             
	char jisukopen                        [  8];	char _jisukopen;                          //시가지수             
	char jisukhigh                        [  8];	char _jisukhigh;                          //고가지수             
	char jisukhightime                    [  8];	char _jisukhightime;                      //고가시간             
	char jisuklow                         [  8];	char _jisuklow;                           //저가지수             
	char jisuklowtime                     [  8];	char _jisuklowtime;                       //저가시간             
	char jisukchrate                      [  5];	char _jisukchrate;                        //지수등락률           
	char jisukbrkvol                      [  5];	char _jisukbrkvol;                        //거래비중             
} Tk1OutBlock;

typedef struct tagk1
{
	Tk1InBlock                        k1inblock                             ;  //입력 
	Tk1OutBlock                       k1outblock                            ;  //출력 
} Tk1;


typedef struct tagj0InBlock    //입력
{
	char code                             [  6];	char _code;                               //종목코드             
} Tj0InBlock;

typedef struct tagj0OutBlock    //출력
{
	char code                             [  6];	char _code;                               //종목코드             
	char time                             [  8];	char _time;                               //시간                 
	char nsign                            [  1];	char _nsign;                              //등락부호             
	char nchange                          [  9];	char _nchange;                            //등락폭               
	char nav                              [  9];	char _nav;                                //NAV현재가            
	char nopen                            [  9];	char _nopen;                              //NAV시가              
	char nhigh                            [  9];	char _nhigh;                              //NAV고가              
	char nlow                             [  9];	char _nlow;                               //NAV저가              
	char tsign                            [  1];	char _tsign;                              //추적부호             
	char terror                           [  9];	char _terror;                             //추적오차율           
	char gsign                            [  1];	char _gsign;                              //괴리부호             
	char grate                            [  9];	char _grate;                              //괴리율               
} Tj0OutBlock;

typedef struct tagj0
{
	Tj0InBlock                        j0inblock                             ;  //입력 
	Tj0OutBlock                       j0outblock                            ;  //출력 
} Tj0;


typedef struct tagj1InBlock    //입력
{
	char code                             [  6];	char _code;                               //종목코드             
} Tj1InBlock;

typedef struct tagj1OutBlock    //출력
{
	char code                             [  6];	char _code;                               //종목코드             
	char time                             [  8];	char _time;                               //시간                 
	char nsign                            [  1];	char _nsign;                              //등락부호             
	char nchange                          [  9];	char _nchange;                            //등락폭               
	char nav                              [  9];	char _nav;                                //NAV현재가            
	char nopen                            [  9];	char _nopen;                              //NAV시가              
	char nhigh                            [  9];	char _nhigh;                              //NAV고가              
	char nlow                             [  9];	char _nlow;                               //NAV저가              
	char tsign                            [  1];	char _tsign;                              //추적부호             
	char terror                           [  9];	char _terror;                             //추적오차율           
	char gsign                            [  1];	char _gsign;                              //괴리부호             
	char grate                            [  9];	char _grate;                              //괴리율               
} Tj1OutBlock;

typedef struct tagj1
{
	Tj1InBlock                        j1inblock                             ;  //입력 
	Tj1OutBlock                       j1outblock                            ;  //출력 
} Tj1;



// 2025년 3월 4일 대체거래소 제동 이후 추가된 내용



// 주식 현재가 조회
typedef struct tagIVWUTKMST04In    //기본입력
{
	char form_lang[1];	char _form_lang;                          //한영구분             /*k:KOREANe:ENGLISH*/
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             /*6자리종목코드*/
} TIVWUTKMST04In;

typedef struct tagIVWUTKMST04Out1    //종목마스타기본자료
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             /*6자리종목코드*/
	char hts_isnm[41];	char _hts_isnm;                           //종목명               
	char stck_prpr[10];	char _stck_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[10];	char _prdy_vrss;                          //등락폭               
	char prdy_ctrt[5];	char _prdy_ctrt;                          //등락률               
	char askp[10];	char _askp;                               //매도호가             
	char bidp[10];	char _bidp;                               //매수호가             
	char acml_vol[12];	char _acml_vol;                           //거래량               
	char vol_rate[6];	char _vol_rate;                           //거래비율             
	char move_rate[6];	char _move_rate;                          //유동주회전율         
	char acml_tr_pbmn[18];	char _acml_tr_pbmn;                       //거래대금             
	char stck_mxpr[10];	char _stck_mxpr;                          //상한가               
	char stck_hgpr[10];	char _stck_hgpr;                          //고가                 
	char stck_oprc[10];	char _stck_oprc;                          //시가                 
	char stck_oprc_sign[1];	char _stck_oprc_sign;                     //시가대비부호         
	char stck_oprc_vrss[10];	char _stck_oprc_vrss;                     //시가대비등락폭       
	char stck_lwpr[10];	char _stck_lwpr;                          //저가                 
	char stck_llam[10];	char _stck_llam;                          //하한가               
	char hoga_bsop_hour[8];	char _hoga_bsop_hour;                     //호가시간             
	char askp1[10];	char _askp1;                              //매도호가1            
	char askp2[10];	char _askp2;                              //매도호가2            
	char askp3[10];	char _askp3;                              //매도호가3            
	char askp4[10];	char _askp4;                              //매도호가4            
	char askp5[10];	char _askp5;                              //매도호가5            
	char askp6[10];	char _askp6;                              //매도호가6            
	char askp7[10];	char _askp7;                              //매도호가7            
	char askp8[10];	char _askp8;                              //매도호가8            
	char askp9[10];	char _askp9;                              //매도호가9            
	char askp10[10];	char _askp10;                             //매도호가10           
	char bidp1[10];	char _bidp1;                              //매수호가1            
	char bidp2[10];	char _bidp2;                              //매수호가2            
	char bidp3[10];	char _bidp3;                              //매수호가3            
	char bidp4[10];	char _bidp4;                              //매수호가4            
	char bidp5[10];	char _bidp5;                              //매수호가5            
	char bidp6[10];	char _bidp6;                              //매수호가6            
	char bidp7[10];	char _bidp7;                              //매수호가7            
	char bidp8[10];	char _bidp8;                              //매수호가8            
	char bidp9[10];	char _bidp9;                              //매수호가9            
	char bidp10[10];	char _bidp10;                             //매수호가10           
	char askp_rsqn1[12];	char _askp_rsqn1;                         //매도호가잔량1        
	char askp_rsqn2[12];	char _askp_rsqn2;                         //매도호가잔량2        
	char askp_rsqn3[12];	char _askp_rsqn3;                         //매도호가잔량3        
	char askp_rsqn4[12];	char _askp_rsqn4;                         //매도호가잔량4        
	char askp_rsqn5[12];	char _askp_rsqn5;                         //매도호가잔량5        
	char askp_rsqn6[12];	char _askp_rsqn6;                         //매도호가잔량6        
	char askp_rsqn7[12];	char _askp_rsqn7;                         //매도호가잔량7        
	char askp_rsqn8[12];	char _askp_rsqn8;                         //매도호가잔량8        
	char askp_rsqn9[12];	char _askp_rsqn9;                         //매도호가잔량9        
	char askp_rsqn10[12];	char _askp_rsqn10;                        //매도호가잔량10       
	char bidp_rsqn1[12];	char _bidp_rsqn1;                         //매수호가잔량1        
	char bidp_rsqn2[12];	char _bidp_rsqn2;                         //매수호가잔량2        
	char bidp_rsqn3[12];	char _bidp_rsqn3;                         //매수호가잔량3        
	char bidp_rsqn4[12];	char _bidp_rsqn4;                         //매수호가잔량4        
	char bidp_rsqn5[12];	char _bidp_rsqn5;                         //매수호가잔량5        
	char bidp_rsqn6[12];	char _bidp_rsqn6;                         //매수호가잔량6        
	char bidp_rsqn7[12];	char _bidp_rsqn7;                         //매수호가잔량7        
	char bidp_rsqn8[12];	char _bidp_rsqn8;                         //매수호가잔량8        
	char bidp_rsqn9[12];	char _bidp_rsqn9;                         //매수호가잔량9        
	char bidp_rsqn10[12];	char _bidp_rsqn10;                        //매수호가잔량10       
	char total_askp_rsqn[12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn[12];	char _total_bidp_rsqn;                    //총매수잔량           
	char ovtm_askp_rsqn[12];	char _ovtm_askp_rsqn;                     //시간외매도잔량       
	char ovtm_bidp_rsqn[12];	char _ovtm_bidp_rsqn;                     //시간외매수잔량       
	char pvt_scnd_dmrs[10];	char _pvt_scnd_dmrs;                      //피봇2차저항          
	char pvt_frst_dmrs[10];	char _pvt_frst_dmrs;                      //피봇1차저항          
	char pvt_pont_val[10];	char _pvt_pont_val;                       //피봇가               
	char pvt_frst_dmsp[10];	char _pvt_frst_dmsp;                      //피봇1차지지          
	char pvt_scnd_dmsp[10];	char _pvt_scnd_dmsp;                      //피봇2차지지          
	char mrkt_div_isnm[6];	char _mrkt_div_isnm;                      //코스피코스닥구분     
	char bstp_kor_isnm[40];	char _bstp_kor_isnm;                      //업종명               /*명칭앞에있던업종코드부분을분리48->40변경*/
	char bstp_cls_code[6];	char _bstp_cls_code;                      //업종코드             /*업종명에있던업종코드를분리*/
	char avls_scal_isnm[6];	char _avls_scal_isnm;                     //자본금규모           
	char stac_month[16];	char _stac_month;                         //결산월               
	char marcket1z16[16];	char _marcket1z16;                        //시장조치1            
	char marcket2z16[16];	char _marcket2z16;                        //시장조치2            
	char marcket3z16[16];	char _marcket3z16;                        //시장조치3            
	char marcket4z16[16];	char _marcket4z16;                        //시장조치4            
	char marcket5z16[16];	char _marcket5z16;                        //시장조치5            
	char marcket6z16[16];	char _marcket6z16;                        //시장조치6            
	char cb_text[6];	char _cb_text;                            //CB구분               
	char stck_fcam[10];	char _stck_fcam;                          //액면가               
	char prdy_clpr_title[12];	char _prdy_clpr_title;                    //전일종가타이틀       
	char stck_prdy_clpr[10];	char _stck_prdy_clpr;                     //전일종가             
	char stck_sspr[10];	char _stck_sspr;                          //대용가               
	char gongpricez7[7];	char _gongpricez7;                        //공모가               
	char d5_hgpr[10];	char _d5_hgpr;                            //5일고가              
	char d5_lwpr[10];	char _d5_lwpr;                            //5일저가              
	char d20_hgpr[10];	char _d20_hgpr;                           //20일고가             
	char d20_lwpr[10];	char _d20_lwpr;                           //20일저가             
	char w52_hgpr[10];	char _w52_hgpr;                           //52주최고가           
	char w52_hgpr_date[4];	char _w52_hgpr_date;                      //52주최고가일         
	char w52_lwpr[10];	char _w52_lwpr;                           //52주최저가           
	char w52_lwpr_date[4];	char _w52_lwpr_date;                      //52주최저가일         
	char move_stcn[12];	char _move_stcn;                          //유동주식수           
	char lstn_stcn_unit3[12];	char _lstn_stcn_unit3;                    //상장주식수           
	char hts_avls[12];	char _hts_avls;                           //시가총액             
	char memb_bsop_hour[5];	char _memb_bsop_hour;                     //시간                 
	char seln_mbcr_name1[6];	char _seln_mbcr_name1;                    //매도거래원1          
	char shnu_mbcr_name1[6];	char _shnu_mbcr_name1;                    //매수거래원1          
	char seln_qty1[12];	char _seln_qty1;                          //매도거래량1          
	char shnu_qty1[12];	char _shnu_qty1;                          //매수거래량1          
	char seln_mbcr_name2[6];	char _seln_mbcr_name2;                    //매도거래원2          
	char shnu_mbcr_name2[6];	char _shnu_mbcr_name2;                    //매수거래원2          
	char seln_qty2[12];	char _seln_qty2;                          //매도거래량2          
	char shnu_qty2[12];	char _shnu_qty2;                          //매수거래량2          
	char seln_mbcr_name3[6];	char _seln_mbcr_name3;                    //매도거래원3          
	char shnu_mbcr_name3[6];	char _shnu_mbcr_name3;                    //매수거래원3          
	char seln_qty3[12];	char _seln_qty3;                          //매도거래량3          
	char shnu_qty3[12];	char _shnu_qty3;                          //매수거래량3          
	char seln_mbcr_name4[6];	char _seln_mbcr_name4;                    //매도거래원4          
	char shnu_mbcr_name4[6];	char _shnu_mbcr_name4;                    //매수거래원4          
	char seln_qty4[12];	char _seln_qty4;                          //매도거래량4          
	char shnu_qty4[12];	char _shnu_qty4;                          //매수거래량4          
	char seln_mbcr_name5[6];	char _seln_mbcr_name5;                    //매도거래원5          
	char shnu_mbcr_name5[6];	char _shnu_mbcr_name5;                    //매수거래원5          
	char seln_qty5[12];	char _seln_qty5;                          //매도거래량5          
	char shnu_qty5[12];	char _shnu_qty5;                          //매수거래량5          
	char glob_seln_qty[12];	char _glob_seln_qty;                      //매도외국인거래량     
	char glob_shnu_qty[12];	char _glob_shnu_qty;                      //매수외국인거래량     
	char for_hour[6];	char _for_hour;                           //외국인시간           
	char for_rate[5];	char _for_rate;                           //외국인지분율         
	char crdt_stlm_date[4];	char _crdt_stlm_date;                     //결제일               
	char crdt_rmnd_rate[5];	char _crdt_rmnd_rate;                     //잔고비율(%)          
	char yu_date[4];	char _yu_date;                            //유상기준일           
	char mu_date[4];	char _mu_date;                            //무상기준일           
	char yu_rate[5];	char _yu_rate;                            //유상배정비율         
	char mu_rate[5];	char _mu_rate;                            //무상배정비율         
	char frgn_ntby_vol[10];	char _frgn_ntby_vol;                      //외국인변동주수       
	char jasa[1];	char _jasa;                               //자사주               
	char stck_lstn_date[8];	char _stck_lstn_date;                     //상장일               
	char dae_rate[5];	char _dae_rate;                           //대주주지분율         
	char dae_date[6];	char _dae_date;                           //대주주지분일자       
	char filler[1];	char _filler;                             //FILLER               
	char deposit_gb[1];	char _deposit_gb;                         //증거금율             
	char cpfn[12];	char _cpfn;                               //자본금               
	char total_seln_qty[12];	char _total_seln_qty;                     //전체거래원매도합     
	char total_shnu_qty[12];	char _total_shnu_qty;                     //전체거래원매수합     
	char detour_gb[1];	char _detour_gb;                          //우회상장여부         
	char scrt_grp_isnm[6];	char _scrt_grp_isnm;                      //증권구분             
	char crdt_deal_date[4];	char _crdt_deal_date;                     //공여율기준일         
	char crdt_loan_gvrt[5];	char _crdt_loan_gvrt;                     //공여율(%)            
	char per[5];	char _per;                                //PER                  
	char hando_gb[1];	char _hando_gb;                           //종목별신용한도       
	char wghn_avrg_prc[10];	char _wghn_avrg_prc;                      //가중가               
	char lstn_stcn_unit0[12];	char _lstn_stcn_unit0;                    //상장주식수_주        
	char add_lstn_stcn[12];	char _add_lstn_stcn;                      //추가상장주수         
	char gicomment[100];	char _gicomment;                          //종목comment          
	char prdy_vol[12];	char _prdy_vol;                           //전일거래량           
	char pre_prdy_sign[1];	char _pre_prdy_sign;                      //전일대비등락부호     
	char pre_prdy_vrss[10];	char _pre_prdy_vrss;                      //전일대비등락폭       
	char stck_dryy_hgpr[10];	char _stck_dryy_hgpr;                     //연종최고가           
	char dryy_hgpr_date[4];	char _dryy_hgpr_date;                     //연중최고가일         
	char stck_dryy_lwpr[10];	char _stck_dryy_lwpr;                     //연중최저가           
	char dryy_lwpr_date[4];	char _dryy_lwpr_date;                     //연중최저가일         
	char frgn_hldn_qty[15];	char _frgn_hldn_qty;                      //외국인보유주식수     
	char issu_limt_rate[5];	char _issu_limt_rate;                     //외국인한도율(%)      
	char frml_mrkt_unit[5];	char _frml_mrkt_unit;                     //매매수량단위         
	char comp_cls_code[1];	char _comp_cls_code;                      //경쟁대량방향구분     
	char largem_gb[1];	char _largem_gb;                          //대량매매구분         
	char pbr[5];	char _pbr;                                //PBR                  
	char dmrs_val[7];	char _dmrs_val;                           //디저항값             
	char dmsp_val[7];	char _dmsp_val;                           //디지지값             
	char prdy_tr_pbmn[12];	char _prdy_tr_pbmn;                       //전일거래대금         
	char vi_antc_sdpr[10];	char _vi_antc_sdpr;                       //VI기준가             
	char vi_antc_mxpr[10];	char _vi_antc_mxpr;                       //VI상승발동가         
	char vi_antc_llam[10];	char _vi_antc_llam;                       //VI하락발동가         
	char invt_epmd_yn[1];	char _invt_epmd_yn;                       //투자유의종목여부     
	char uplm_qty[12];	char _uplm_qty;                           //상한수량             
	char short_over_code[1];	char _short_over_code;                    //단기과열구분코드     /*1:단기과열예고,2:단기과열지정,3:단기과열연장*/
	char mrkt_alrm_code[1];	char _mrkt_alrm_code;                     //투자주의경고구분코드 /*1:투자주의,2:투자경고,3:투자주의>투자위험예고,4:투자경고투자위험예고,5:투자위험*/
	char sltr_yn[1];	char _sltr_yn;                            //정리매매여부         /*Y:정리매매종목*/
	char crd_rt_grd_nm[6];	char _crd_rt_grd_nm;                      //담보유지비율(%)      
	char mid_prc[10];	char _mid_prc;                            //중간가               
	char midp_total_askp_rsqn[12];	char _midp_total_askp_rsqn;               //매도중간가잔량합계수량 
	char midp_total_bidp_rsqn[12];	char _midp_total_bidp_rsqn;               //매수중간가잔량합계수량 
	char nxt_mid_prc[10];	char _nxt_mid_prc;                        //nxt중간가            
	char nxt_midp_total_askp_rsqn[12];	char _nxt_midp_total_askp_rsqn;           //nxt매도중간가잔량합계수량 
	char nxt_midp_total_bidp_rsqn[12];	char _nxt_midp_total_bidp_rsqn;           //nxt매수중간가잔량합계수량 
} TIVWUTKMST04Out1;

typedef struct tagIVWUTKMST04Out2    //변동거래량자료, [반복]
{
	char bsop_hour[8];	char _bsop_hour;                          //시간                 
	char stck_prpr[10];	char _stck_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[10];	char _prdy_vrss;                          //등락폭               
	char askp[10];	char _askp;                               //매도호가             
	char bidp[10];	char _bidp;                               //매수호가             
	char cntg_vol[12];	char _cntg_vol;                           //변동거래량           
	char acml_vol[12];	char _acml_vol;                           //거래량               
} TIVWUTKMST04Out2;

typedef struct tagIVWUTKMST04Out3    //종목지표
{
	char cncc_aspr_code[1];	char _cncc_aspr_code;                     //동시호가구분         
	char antc_cnpr[10];	char _antc_cnpr;                          //예상체결가           
	char antc_cntg_sign[1];	char _antc_cntg_sign;                     //예상체결부호         
	char antc_cntg_vrss[10];	char _antc_cntg_vrss;                     //예상체결등락폭       
	char antc_prdy_ctrt[5];	char _antc_prdy_ctrt;                     //예상체결등락률       
	char antc_vol[12];	char _antc_vol;                           //예상체결수량         
	char chkdataz1[1];	char _chkdataz1;                          //ECN정보유무구분      
	char ovtm_untp_prpr[10];	char _ovtm_untp_prpr;                     //ECN전일종가          
	char ovtm_untp_sign[1];	char _ovtm_untp_sign;                     //ECN부호              
	char ovtm_untp_vrss[10];	char _ovtm_untp_vrss;                     //ECN등락폭            
	char ovtm_untp_ctrt[5];	char _ovtm_untp_ctrt;                     //ECN등락률            
	char ovtm_untp_vol[12];	char _ovtm_untp_vol;                      //ECN체결수량          
	char ovtm_antc_sign[1];	char _ovtm_antc_sign;                     //ECN대비예상체결부호  
	char ovtm_antc_vrss[10];	char _ovtm_antc_vrss;                     //ECN대비예상체결등락폭 
	char ovtm_antc_ctrt[5];	char _ovtm_antc_ctrt;                     //ECN대비예상체결등락률 
	char scoring[6];	char _scoring;                            //종합스코어링         
	char vi_type_code[1];	char _vi_type_code;                       //VI거래중지여부       /*1:VI발동,N:그외*/
} TIVWUTKMST04Out3;

typedef struct tagIVWUTKMST04
{
	TIVWUTKMST04In                    IVWUTKMST04in;  //기본입력 
	TIVWUTKMST04Out1                  IVWUTKMST04out1;  //종목마스타기본자료 
	TIVWUTKMST04Out2                  IVWUTKMST04out2[20];  //변동거래량자료 , [반복]
	TIVWUTKMST04Out3                  IVWUTKMST04out3;  //종목지표 
} TIVWUTKMST04;

typedef struct tagIVWFUTREQ02In    //기본입력
{
	char formlang[1];	char _formlang;                           //한영구분             /*k:KOREANe:ENGLISH*/
	char shrn_iscd[9];	char _shrn_iscd;                          //종목코드             
} TIVWFUTREQ02In;

typedef struct tagIVWFUTREQ02Out1    //종목마스타기본자료
{
	char shrn_iscd[8];	char _shrn_iscd;                          //종목코드             
	char ftop_kor_isnm[80];	char _ftop_kor_isnm;                      //종목명               
	char futs_prpr[8];	char _futs_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char futs_prdy_vrss[8];	char _futs_prdy_vrss;                     //등락폭               
	char futs_prdy_ctrt[5];	char _futs_prdy_ctrt;                     //등락률               
	char mrkt_basis[8];	char _mrkt_basis;                         //베이시스             
	char hts_thpr[8];	char _hts_thpr;                           //이론가               
	char dprt_value[8];	char _dprt_value;                         //괴리도               
	char dprt[8];	char _dprt;                               //괴리율               
	char acml_vol[12];	char _acml_vol;                           //거래량               
	char acml_tr_pbmn[12];	char _acml_tr_pbmn;                       //누적거래대금(백만)   
	char otst_qty[12];	char _otst_qty;                           //미결제약정수량       
	char prdy_otst_qty[12];	char _prdy_otst_qty;                      //미결제약정전일       
	char futs_mxpr[8];	char _futs_mxpr;                          //상한가               
	char futs_hgpr[8];	char _futs_hgpr;                          //고가                 
	char futs_oprc[8];	char _futs_oprc;                          //시가                 
	char oprc_vrss_sign[1];	char _oprc_vrss_sign;                     //시가대비부호         
	char oprc_vrss[8];	char _oprc_vrss;                          //시가대비등락         
	char futs_lwpr[8];	char _futs_lwpr;                          //저가                 
	char futs_llam[8];	char _futs_llam;                          //하한가               
	char futs_bhprice[8];	char _futs_bhprice;                       //CB발동상한           
	char futs_blprice[8];	char _futs_blprice;                       //CB발동하한           
	char dmrs[8];	char _dmrs;                               //DEMARK저항           
	char dmsp[8];	char _dmsp;                               //DEMARK지지           
	char lstn_medm_hgpr[8];	char _lstn_medm_hgpr;                     //상장후최고가         
	char lstn_hgpr_date[8];	char _lstn_hgpr_date;                     //상장후최고일         
	char lstn_medm_lwpr[8];	char _lstn_medm_lwpr;                     //상장후최저가         
	char lstn_lwpr_date[8];	char _lstn_lwpr_date;                     //상장후최저일         
	char last_tr_date[8];	char _last_tr_date;                       //최종거래일           
	char hts_rmnn_dynu[3];	char _hts_rmnn_dynu;                      //잔존일               
	char cd_mnrt[6];	char _cd_mnrt;                            //무위험이자율         
	char bsop_hour[8];	char _bsop_hour;                          //호가시간             
	char futs_askp1[8];	char _futs_askp1;                         //매도최우선호가       
	char futs_askp2[8];	char _futs_askp2;                         //매도차선호가         
	char futs_askp3[8];	char _futs_askp3;                         //매도차차선호가       
	char futs_askp4[8];	char _futs_askp4;                         //매도4차선호가        
	char futs_askp5[8];	char _futs_askp5;                         //매도5차선호가        
	char futs_bidp1[8];	char _futs_bidp1;                         //매수최우선호가       
	char futs_bidp2[8];	char _futs_bidp2;                         //매수차선호가         
	char futs_bidp3[8];	char _futs_bidp3;                         //매수차차선호가       
	char futs_bidp4[8];	char _futs_bidp4;                         //매수4차선호가        
	char futs_bidp5[8];	char _futs_bidp5;                         //매수5차선호가        
	char askp_rsqn1[12];	char _askp_rsqn1;                         //매도최우선잔량       
	char askp_rsqn2[12];	char _askp_rsqn2;                         //매도차선잔량         
	char askp_rsqn3[12];	char _askp_rsqn3;                         //매도차차선잔량       
	char askp_rsqn4[12];	char _askp_rsqn4;                         //매도4차선잔량        
	char askp_rsqn5[12];	char _askp_rsqn5;                         //매도5차선잔량        
	char bidp_rsqn1[12];	char _bidp_rsqn1;                         //매수최우선잔량       
	char bidp_rsqn2[12];	char _bidp_rsqn2;                         //매수차선잔량         
	char bidp_rsqn3[12];	char _bidp_rsqn3;                         //매수차차선잔량       
	char bidp_rsqn4[12];	char _bidp_rsqn4;                         //매수4차선잔량        
	char bidp_rsqn5[12];	char _bidp_rsqn5;                         //매수5차선잔량        
	char total_askp_rsqn[12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn[12];	char _total_bidp_rsqn;                    //총매수잔량           
	char askp_csnu1[10];	char _askp_csnu1;                         //매도최우선건수       
	char askp_csnu2[10];	char _askp_csnu2;                         //매도차선건수         
	char askp_csnu3[10];	char _askp_csnu3;                         //매도차차선건수       
	char askp_csnu4[10];	char _askp_csnu4;                         //매도4차선건수        
	char askp_csnu5[10];	char _askp_csnu5;                         //매도5차선건수        
	char bidp_csnu1[10];	char _bidp_csnu1;                         //매수최우선건수       
	char bidp_csnu2[10];	char _bidp_csnu2;                         //매수차선건수         
	char bidp_csnu3[10];	char _bidp_csnu3;                         //매수차차선건수       
	char bidp_csnu4[10];	char _bidp_csnu4;                         //매수4차선건수        
	char bidp_csnu5[10];	char _bidp_csnu5;                         //매수5차선건수        
	char total_askp_csnu[10];	char _total_askp_csnu;                    //총매도건수           
	char total_bidp_csnu[10];	char _total_bidp_csnu;                    //총매수건수           
	char pvt_scnd_dmrs[8];	char _pvt_scnd_dmrs;                      //피봇2차저항          
	char pvt_frst_dmrs[8];	char _pvt_frst_dmrs;                      //피봇1차저항          
	char pvt_pont[8];	char _pvt_pont;                           //피봇가               
	char pvt_frst_dmsp[8];	char _pvt_frst_dmsp;                      //피봇1차지지          
	char pvt_scnd_dmsp[8];	char _pvt_scnd_dmsp;                      //피봇2차지지          
	char fujgubun[8];	char _fujgubun;                           //CB발동여부           
	char spead_acml_vol[12];	char _spead_acml_vol;                     //스프레드거래량       
	char dmix_wrth_val[9];	char _dmix_wrth_val;                      //배당액지수           
	char futs_prdy_clpr[8];	char _futs_prdy_clpr;                     //전일종가             
	char dynmc_uplmtprc[8];	char _dynmc_uplmtprc;                     //실시간상한가         
	char dynmc_lwlmtprc[8];	char _dynmc_lwlmtprc;                     //실시간하한가         
	char dynmc_prc_lmt_yn[1];	char _dynmc_prc_lmt_yn;                   //동적가격제한여부     
	char dscs_lrqn_vol[12];	char _dscs_lrqn_vol;                      //협의거래량           
	char prc_lmt_exlmtgb[1];	char _prc_lmt_exlmtgb;                    //가격확대예정구분     
	char prc_lmt_mx_step[2];	char _prc_lmt_mx_step;                    //가격제한확대상한단계 
	char prc_lmt_ll_step[2];	char _prc_lmt_ll_step;                    //가격제한확대하한단계 
	char futs_sdpr[8];	char _futs_sdpr;                          //기준가               
	char ther_basis[8];	char _ther_basis;                         //이론베이시스         
} TIVWFUTREQ02Out1;

typedef struct tagIVWFUTREQ02Out2    //코스피200지수
{
	char fu_item[8];	char _fu_item;                            //코스피200코드        
	char prpr_nmix[8];	char _prpr_nmix;                          //코스피200지수        
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //코스피200등락부호    
	char nmix_prdy_vrss[8];	char _nmix_prdy_vrss;                     //코스피200등락폭      
	char nmix_prdy_ctrt[5];	char _nmix_prdy_ctrt;                     //코스피200등락률      
} TIVWFUTREQ02Out2;

typedef struct tagIVWFUTREQ02Out3    //변동거래량자료, [반복]
{
	char bsop_hour[8];	char _bsop_hour;                          //시간                 
	char futs_prpr[8];	char _futs_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char futs_prdy_vrss[8];	char _futs_prdy_vrss;                     //등락폭               
	char futs_askp[8];	char _futs_askp;                          //매도호가             
	char futs_bidp[8];	char _futs_bidp;                          //매수호가             
	char cnqn[12];	char _cnqn;                               //거래량               
	char acml_vol[12];	char _acml_vol;                           //누적거래량           
	char otst_qty[12];	char _otst_qty;                           //미결제약정수량       
} TIVWFUTREQ02Out3;

typedef struct tagIVWFUTREQ02Out4    //시간대별투자자현황최근메모리, [반복]
{
	char titlez6[6];	char _titlez6;                            //TITLE                
	char ntby_vol[12];	char _ntby_vol;                           //순매수               
	char seln_vol[12];	char _seln_vol;                           //매도                 
	char shnu_vol[12];	char _shnu_vol;                           //매수                 
} TIVWFUTREQ02Out4;

typedef struct tagIVWFUTREQ02Out5    //시간대별투자자현황시간별, [반복]
{
	char bsop_hour[8];	char _bsop_hour;                          //시간별               
	char frgn_ntby_vol[12];	char _frgn_ntby_vol;                      //외국인순매수         
	char scrt_ntby_vol[12];	char _scrt_ntby_vol;                      //증권순매수           
	char prsn_ntby_vol[12];	char _prsn_ntby_vol;                      //개인순매수           
} TIVWFUTREQ02Out5;

typedef struct tagIVWFUTREQ02Out6    //KOSPI200시가총액상위10종목, [반복]
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             
	char hts_kor_isnm[40];	char _hts_kor_isnm;                       //종목명               
	char stck_fcam[10];	char _stck_fcam;                          //액면가               
	char stck_prpr[10];	char _stck_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[10];	char _prdy_vrss;                          //등락폭               
	char prdy_ctrt[5];	char _prdy_ctrt;                          //등락률               
} TIVWFUTREQ02Out6;

typedef struct tagIVWFUTREQ02Out7    //예상체결
{
	char dongsi[1];	char _dongsi;                             //동시호가구분         
	char futs_antc_cnpr[8];	char _futs_antc_cnpr;                     //예상체결가           
	char futs_antc_sign[1];	char _futs_antc_sign;                     //예상체결부호         
	char futs_antc_vrss[8];	char _futs_antc_vrss;                     //예상체결등락폭       
	char futs_antc_ctrt[5];	char _futs_antc_ctrt;                     //예상체결등락률       
	char antc_cnqn[9];	char _antc_cnqn;                          //예상체결수량         //파생시장제도개선(2024.03.13)
} TIVWFUTREQ02Out7;

typedef struct tagIVWFUTREQ02
{
	TIVWFUTREQ02In                    ivwfutreq02in;  //기본입력 
	TIVWFUTREQ02Out1                  ivwfutreq02out1;  //종목마스타기본자료 
	TIVWFUTREQ02Out2                  ivwfutreq02out2;  //코스피200지수 
	TIVWFUTREQ02Out3                  ivwfutreq02out3[30];  //변동거래량자료 , [반복]
	TIVWFUTREQ02Out4                  ivwfutreq02out4[3];  //시간대별투자자현황최근메모리 , [반복]
	TIVWFUTREQ02Out5                  ivwfutreq02out5[20];  //시간대별투자자현황시간별 , [반복]
	TIVWFUTREQ02Out6                  ivwfutreq02out6[10];  //KOSPI200시가총액상위10종목 , [반복]
	TIVWFUTREQ02Out7                  ivwfutreq02out7;  //예상체결 
} TIVWFUTREQ02;

typedef struct tagIVWFUTREQ08In    //입력데이타
{
	char shrn_iscd                        [  9];	char _shrn_iscd;                          //입력코드             
} TIVWFUTREQ08In;

typedef struct tagIVWFUTREQ08Out1    //IVWFUTREQ08OutKospi200
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char prpr_nmix                        [  9];	char _prpr_nmix;                          //현물지수             
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //전일비부호           
	char futs_prdy_vrss                   [  9];	char _futs_prdy_vrss;                     //전일비               
	char futs_oprc                        [  9];	char _futs_oprc;                          //시가                 
	char futs_hgpr                        [  9];	char _futs_hgpr;                          //고가                 
	char futs_lwpr                        [  9];	char _futs_lwpr;                          //저가                 
	char acml_vol                         [ 12];	char _acml_vol;                           //거래량               
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUTREQ08Out1;

typedef struct tagIVWFUTREQ08Out2    //IVWFUTREQ08OutSMaster
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char futs_prpr                        [  6];	char _futs_prpr;                          //현재가               
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //전일비부호           
	char futs_prdy_vrss                   [  9];	char _futs_prdy_vrss;                     //전일비               
	char futs_prdy_ctrt                   [  5];	char _futs_prdy_ctrt;                     //등락률               
	char futs_oprc                        [  9];	char _futs_oprc;                          //시가                 
	char futs_hgpr                        [  9];	char _futs_hgpr;                          //고가                 
	char futs_lwpr                        [  9];	char _futs_lwpr;                          //저가                 
	char acml_vol                         [ 12];	char _acml_vol;                           //거래량               
	char acml_tr_pbmn                     [ 18];	char _acml_tr_pbmn;                       //누적거래대금(백만원) 
	char fuspcurr1                        [  9];	char _fuspcurr1;                          //의제약정가(근월물)   
	char fuspcurr2                        [  9];	char _fuspcurr2;                          //의제약정가(원월물)   
	char dynmc_uplmtprc                   [  9];	char _dynmc_uplmtprc;                     //실시간상한가         
	char dynmc_lwlmtprc                   [  9];	char _dynmc_lwlmtprc;                     //실시간하한가         
	char fudynpriceflag                   [  1];	char _fudynpriceflag;                     //동적가격제한여부     
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUTREQ08Out2;

typedef struct tagIVWFUTREQ08Out3    //코스피선물Master1
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char bsop_hour                        [  8];	char _bsop_hour;                          //체결시간             
	char ftop_kor_isnm                    [ 12];	char _ftop_kor_isnm;                      //한글명               
	char futs_prpr                        [  9];	char _futs_prpr;                          //현재가               
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //전일대비부호         
	char futs_prdy_vrss                   [  9];	char _futs_prdy_vrss;                     //전일대비             
	char futs_prdy_ctrt                   [  5];	char _futs_prdy_ctrt;                     //등락률               
	char mrkt_basis                       [  9];	char _mrkt_basis;                         //베이시스             
	char hts_thpr                         [  9];	char _hts_thpr;                           //이론가               
	char fugrate                          [  9];	char _fugrate;                            //괴리도               
	char fugratio                         [  5];	char _fugratio;                           //괴리율               
	char acml_vol                         [ 12];	char _acml_vol;                           //누적체결수량         
	char acml_tr_pbmn                     [ 18];	char _acml_tr_pbmn;                       //누적거래대금(백만원) 
	char fuopenyak                        [ 12];	char _fuopenyak;                          //미결제약정수량       
	char fupreopenyak                     [ 12];	char _fupreopenyak;                       //미결제약정전일       
	char fujgubun                         [  8];	char _fujgubun;                           //장운용               
	char futs_oprc                        [  9];	char _futs_oprc;                          //시가                 
	char futs_hgpr                        [  9];	char _futs_hgpr;                          //고가                 
	char futs_lwpr                        [  9];	char _futs_lwpr;                          //저가                 
	char dynmc_uplmtprc                   [  9];	char _dynmc_uplmtprc;                     //실시간상한가         
	char dynmc_lwlmtprc                   [  9];	char _dynmc_lwlmtprc;                     //실시간하한가         
	char fudynpriceflag                   [  1];	char _fudynpriceflag;                     //동적가격제한여부     
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUTREQ08Out3;

typedef struct tagIVWFUTREQ08Out4    //코스피선물Master2
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char bsop_hour                        [  8];	char _bsop_hour;                          //체결시간             
	char ftop_kor_isnm                    [ 12];	char _ftop_kor_isnm;                      //한글명               
	char futs_prpr                        [  9];	char _futs_prpr;                          //현재가               
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //전일대비부호         
	char futs_prdy_vrss                   [  9];	char _futs_prdy_vrss;                     //전일대비             
	char futs_prdy_ctrt                   [  5];	char _futs_prdy_ctrt;                     //등락률               
	char mrkt_basis                       [  9];	char _mrkt_basis;                         //베이시스             
	char hts_thpr                         [  9];	char _hts_thpr;                           //이론가               
	char fugrate                          [  9];	char _fugrate;                            //괴리도               
	char fugratio                         [  5];	char _fugratio;                           //괴리율               
	char acml_vol                         [ 12];	char _acml_vol;                           //누적체결수량         
	char acml_tr_pbmn                     [ 18];	char _acml_tr_pbmn;                       //누적거래대금(백만원) 
	char fuopenyak                        [ 12];	char _fuopenyak;                          //미결제약정수량       
	char fupreopenyak                     [ 12];	char _fupreopenyak;                       //미결제약정전일       
	char fujgubun                         [  8];	char _fujgubun;                           //장운용               
	char futs_oprc                        [  9];	char _futs_oprc;                          //시가                 
	char futs_hgpr                        [  9];	char _futs_hgpr;                          //고가                 
	char futs_lwpr                        [  9];	char _futs_lwpr;                          //저가                 
	char dynmc_uplmtprc                   [  9];	char _dynmc_uplmtprc;                     //실시간상한가         
	char dynmc_lwlmtprc                   [  9];	char _dynmc_lwlmtprc;                     //실시간하한가         
	char fudynpriceflag                   [  1];	char _fudynpriceflag;                     //동적가격제한여부     
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUTREQ08Out4;

typedef struct tagIVWFUTREQ08Out5    //코스피선물호가1
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char bsop_hour                        [  8];	char _bsop_hour;                          //호가시간             
	char futs_askp1                       [  9];	char _futs_askp1;                         //매도우선호가         
	char futs_askp2                       [  9];	char _futs_askp2;                         //차선매도호가         
	char futs_askp3                       [  9];	char _futs_askp3;                         //차차선매도호가       
	char futs_askp4                       [  9];	char _futs_askp4;                         //4차선매도호가        
	char futs_askp5                       [  9];	char _futs_askp5;                         //5차선매도호가        
	char askp_rsqn1                       [ 12];	char _askp_rsqn1;                         //매도잔량             
	char askp_rsqn2                       [ 12];	char _askp_rsqn2;                         //차선매도호가잔량     
	char askp_rsqn3                       [ 12];	char _askp_rsqn3;                         //차차선매도호가잔량   
	char askp_rsqn4                       [ 12];	char _askp_rsqn4;                         //4차선매도호가잔량    
	char askp_rsqn5                       [ 12];	char _askp_rsqn5;                         //5차선매도호가잔량    
	char futs_bidp1                       [  9];	char _futs_bidp1;                         //매수우선호가         
	char futs_bidp2                       [  9];	char _futs_bidp2;                         //차선매수호가         
	char futs_bidp3                       [  9];	char _futs_bidp3;                         //차차선매수호가       
	char futs_bidp4                       [  9];	char _futs_bidp4;                         //4차선매수호가        
	char futs_bidp5                       [  9];	char _futs_bidp5;                         //5차선매수호가        
	char bidp_rsqn1                       [ 12];	char _bidp_rsqn1;                         //매수잔량             
	char bidp_rsqn2                       [ 12];	char _bidp_rsqn2;                         //차선매수호가잔량     
	char bidp_rsqn3                       [ 12];	char _bidp_rsqn3;                         //차차선매수호가잔량   
	char bidp_rsqn4                       [ 12];	char _bidp_rsqn4;                         //4차선매수호가잔량    
	char bidp_rsqn5                       [ 12];	char _bidp_rsqn5;                         //5차선매수호가잔량    
	char total_askp_rsqn                  [ 12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn                  [ 12];	char _total_bidp_rsqn;                    //총매수잔량           
	char askp_csnu1                       [ 10];	char _askp_csnu1;                         //매도최우선건수       
	char askp_csnu2                       [ 10];	char _askp_csnu2;                         //매도차선건수         
	char askp_csnu3                       [ 10];	char _askp_csnu3;                         //매도차차선건수       
	char askp_csnu4                       [ 10];	char _askp_csnu4;                         //매도4차선건수        
	char askp_csnu5                       [ 10];	char _askp_csnu5;                         //매도5차선건수        
	char bidp_csnu1                       [ 10];	char _bidp_csnu1;                         //매수최우선건수       
	char bidp_csnu2                       [ 10];	char _bidp_csnu2;                         //매수차선건수         
	char bidp_csnu3                       [ 10];	char _bidp_csnu3;                         //매수차차선건수       
	char bidp_csnu4                       [ 10];	char _bidp_csnu4;                         //매수4차선건수        
	char bidp_csnu5                       [ 10];	char _bidp_csnu5;                         //매수5차선건수        
	char total_askp_csnu                  [ 10];	char _total_askp_csnu;                    //총매도건수           
	char total_bidp_csnu                  [ 10];	char _total_bidp_csnu;                    //총매수건수           
	char ftop_kor_isnm                    [ 12];	char _ftop_kor_isnm;                      //한글명               
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUTREQ08Out5;

typedef struct tagIVWFUTREQ08Out6    //코스피선물호가2
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char bsop_hour                        [  8];	char _bsop_hour;                          //호가시간             
	char futs_askp1                       [  9];	char _futs_askp1;                         //매도우선호가         
	char futs_askp2                       [  9];	char _futs_askp2;                         //차선매도호가         
	char futs_askp3                       [  9];	char _futs_askp3;                         //차차선매도호가       
	char futs_askp4                       [  9];	char _futs_askp4;                         //4차선매도호가        
	char futs_askp5                       [  9];	char _futs_askp5;                         //5차선매도호가        
	char askp_rsqn1                       [ 12];	char _askp_rsqn1;                         //매도잔량             
	char askp_rsqn2                       [ 12];	char _askp_rsqn2;                         //차선매도호가잔량     
	char askp_rsqn3                       [ 12];	char _askp_rsqn3;                         //차차선매도호가잔량   
	char askp_rsqn4                       [ 12];	char _askp_rsqn4;                         //4차선매도호가잔량    
	char askp_rsqn5                       [ 12];	char _askp_rsqn5;                         //5차선매도호가잔량    
	char futs_bidp1                       [  9];	char _futs_bidp1;                         //매수우선호가         
	char futs_bidp2                       [  9];	char _futs_bidp2;                         //차선매수호가         
	char futs_bidp3                       [  9];	char _futs_bidp3;                         //차차선매수호가       
	char futs_bidp4                       [  9];	char _futs_bidp4;                         //4차선매수호가        
	char futs_bidp5                       [  9];	char _futs_bidp5;                         //5차선매수호가        
	char bidp_rsqn1                       [ 12];	char _bidp_rsqn1;                         //매수잔량             
	char bidp_rsqn2                       [ 12];	char _bidp_rsqn2;                         //차선매수호가잔량     
	char bidp_rsqn3                       [ 12];	char _bidp_rsqn3;                         //차차선매수호가잔량   
	char bidp_rsqn4                       [ 12];	char _bidp_rsqn4;                         //4차선매수호가잔량    
	char bidp_rsqn5                       [ 12];	char _bidp_rsqn5;                         //5차선매수호가잔량    
	char total_askp_rsqn                  [ 12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn                  [ 12];	char _total_bidp_rsqn;                    //총매수잔량           
	char askp_csnu1                       [ 10];	char _askp_csnu1;                         //매도최우선건수       
	char askp_csnu2                       [ 10];	char _askp_csnu2;                         //매도차선건수         
	char askp_csnu3                       [ 10];	char _askp_csnu3;                         //매도차차선건수       
	char askp_csnu4                       [ 10];	char _askp_csnu4;                         //매도4차선건수        
	char askp_csnu5                       [ 10];	char _askp_csnu5;                         //매도5차선건수        
	char bidp_csnu1                       [ 10];	char _bidp_csnu1;                         //매수최우선건수       
	char bidp_csnu2                       [ 10];	char _bidp_csnu2;                         //매수차선건수         
	char bidp_csnu3                       [ 10];	char _bidp_csnu3;                         //매수차차선건수       
	char bidp_csnu4                       [ 10];	char _bidp_csnu4;                         //매수4차선건수        
	char bidp_csnu5                       [ 10];	char _bidp_csnu5;                         //매수5차선건수        
	char total_askp_csnu                  [ 10];	char _total_askp_csnu;                    //총매도건수           
	char total_bidp_csnu                  [ 10];	char _total_bidp_csnu;                    //총매수건수           
	char ftop_kor_isnm                    [ 12];	char _ftop_kor_isnm;                      //한글명               
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUTREQ08Out6;

typedef struct tagIVWFUTREQ08Out7    //코스피선물스프레드호가3
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char ftop_kor_isnm                    [ 12];	char _ftop_kor_isnm;                      //한글명               
	char bsop_hour                        [  8];	char _bsop_hour;                          //호가시간             
	char futs_askp1                       [  9];	char _futs_askp1;                         //매도우선호가         
	char futs_askp2                       [  9];	char _futs_askp2;                         //차선매도호가         
	char futs_askp3                       [  9];	char _futs_askp3;                         //차차선매도호가       
	char futs_askp4                       [  9];	char _futs_askp4;                         //4차선매도호가        
	char futs_askp5                       [  9];	char _futs_askp5;                         //5차선매도호가        
	char askp_rsqn1                       [ 12];	char _askp_rsqn1;                         //매도잔량             
	char askp_rsqn2                       [ 12];	char _askp_rsqn2;                         //차선매도호가잔량     
	char askp_rsqn3                       [ 12];	char _askp_rsqn3;                         //차차선매도호가잔량   
	char askp_rsqn4                       [ 12];	char _askp_rsqn4;                         //4차선매도호가잔량    
	char askp_rsqn5                       [ 12];	char _askp_rsqn5;                         //5차선매도호가잔량    
	char futs_bidp1                       [  9];	char _futs_bidp1;                         //매수우선호가         
	char futs_bidp2                       [  9];	char _futs_bidp2;                         //차선매수호가         
	char futs_bidp3                       [  9];	char _futs_bidp3;                         //차차선매수호가       
	char futs_bidp4                       [  9];	char _futs_bidp4;                         //4차선매수호가        
	char futs_bidp5                       [  9];	char _futs_bidp5;                         //5차선매수호가        
	char bidp_rsqn1                       [ 12];	char _bidp_rsqn1;                         //매수잔량             
	char bidp_rsqn2                       [ 12];	char _bidp_rsqn2;                         //차선매수호가잔량     
	char bidp_rsqn3                       [ 12];	char _bidp_rsqn3;                         //차차선매수호가잔량   
	char bidp_rsqn4                       [ 12];	char _bidp_rsqn4;                         //4차선매수호가잔량    
	char bidp_rsqn5                       [ 12];	char _bidp_rsqn5;                         //5차선매수호가잔량    
	char total_askp_rsqn                  [ 12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn                  [ 12];	char _total_bidp_rsqn;                    //총매수잔량           
	char askp_csnu1                       [ 10];	char _askp_csnu1;                         //매도최우선건수       
	char askp_csnu2                       [ 10];	char _askp_csnu2;                         //매도차선건수         
	char askp_csnu3                       [ 10];	char _askp_csnu3;                         //매도차차선건수       
	char askp_csnu4                       [ 10];	char _askp_csnu4;                         //매도4차선건수        
	char askp_csnu5                       [ 10];	char _askp_csnu5;                         //매도5차선건수        
	char bidp_csnu1                       [ 10];	char _bidp_csnu1;                         //매수최우선건수       
	char bidp_csnu2                       [ 10];	char _bidp_csnu2;                         //매수차선건수         
	char bidp_csnu3                       [ 10];	char _bidp_csnu3;                         //매수차차선건수       
	char bidp_csnu4                       [ 10];	char _bidp_csnu4;                         //매수4차선건수        
	char bidp_csnu5                       [ 10];	char _bidp_csnu5;                         //매수5차선건수        
	char total_askp_csnu                  [ 10];	char _total_askp_csnu;                    //총매도건수           
	char total_bidp_csnu                  [ 10];	char _total_bidp_csnu;                    //총매수건수           
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUTREQ08Out7;

typedef struct tagIVWFUTREQ08Out8    //선물예상체결1
{
	char dongsi                           [  1];	char _dongsi;                             //동시호가구분         
	char jeqprice                         [  9];	char _jeqprice;                           //예상체결가           
	char jeqsign                          [  1];	char _jeqsign;                            //예상체결부호         
	char jeqchange                        [  9];	char _jeqchange;                          //예상체결등락폭       
	char jeqchrate                        [  5];	char _jeqchrate;                          //예상체결등락률       
	char jeqvolume                        [  9];	char _jeqvolume;                          //예상체결수량         //파생시장제도개선(2024.03.13)
	char filler                           [ 21];	char _filler;                             //FILLER               //필러(30->21)
} TIVWFUTREQ08Out8;

typedef struct tagIVWFUTREQ08Out9    //선물예상체결2
{
	char dongsi                           [  1];	char _dongsi;                             //동시호가구분         
	char jeqprice                         [  9];	char _jeqprice;                           //예상체결가           
	char jeqsign                          [  1];	char _jeqsign;                            //예상체결부호         
	char jeqchange                        [  9];	char _jeqchange;                          //예상체결등락폭       
	char jeqchrate                        [  5];	char _jeqchrate;                          //예상체결등락률       
	char jeqvolume                        [  9];	char _jeqvolume;                          //예상체결수량         //파생시장제도개선(2024.03.13)
	char filler                           [ 21];	char _filler;                             //FILLER               //필러(30->21)
} TIVWFUTREQ08Out9;

typedef struct tagIVWFUTREQ08
{
	TIVWFUTREQ08In                    ivwfutreq08in                         ;  //입력데이타 
	TIVWFUTREQ08Out1                  ivwfutreq08out1                       ;  //IVWFUTREQ08OutKospi200 
	TIVWFUTREQ08Out2                  ivwfutreq08out2                       ;  //IVWFUTREQ08OutSMaster 
	TIVWFUTREQ08Out3                  ivwfutreq08out3                       ;  //코스피선물Master1 
	TIVWFUTREQ08Out4                  ivwfutreq08out4                       ;  //코스피선물Master2 
	TIVWFUTREQ08Out5                  ivwfutreq08out5                       ;  //코스피선물호가1 
	TIVWFUTREQ08Out6                  ivwfutreq08out6                       ;  //코스피선물호가2 
	TIVWFUTREQ08Out7                  ivwfutreq08out7                       ;  //코스피선물스프레드호가3 
	TIVWFUTREQ08Out8                  ivwfutreq08out8                       ;  //선물예상체결1 
	TIVWFUTREQ08Out9                  ivwfutreq08out9                       ;  //선물예상체결2 
} TIVWFUTREQ08;

typedef struct tagIVWFUOREQ03In    //기본입력
{
	char formlang                         [  1];	char _formlang;                           //한영구분             /*k:KOREANe:ENGLISH*/
	char shrn_iscd                        [  9];	char _shrn_iscd;                          //종목코드             
} TIVWFUOREQ03In;

typedef struct tagIVWFUOREQ03Out1    //종목마스타기본자료
{
	char shrn_iscd                        [  8];	char _shrn_iscd;                          //종목코드             
	char ftop_eng_isnm                    [ 14];	char _ftop_eng_isnm;                      //종목명               
	char optn_prpr                        [  9];	char _optn_prpr;                          //현재가               
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //등락부호             
	char optn_prdy_vrss                   [  9];	char _optn_prdy_vrss;                     //등락폭               
	char prdy_ctrt                        [  5];	char _prdy_ctrt;                          //등락률               
	char optn_oprc                        [  9];	char _optn_oprc;                          //시가                 
	char optn_hgpr                        [  9];	char _optn_hgpr;                          //고가                 
	char optn_lwpr                        [  9];	char _optn_lwpr;                          //저가                 
	char hts_thpr                         [  9];	char _hts_thpr;                           //이론가               
	char acml_vol                         [ 12];	char _acml_vol;                           //거래량               
	char acml_tr_pbmn                     [ 18];	char _acml_tr_pbmn;                       //누적거래대금(백만)   
	char opopenyak                        [ 12];	char _opopenyak;                          //미결제약정수량       
	char oppreopenyak                     [  7];	char _oppreopenyak;                       //미결제약정전일       
	char oplisthdate                      [ 15];	char _oplisthdate;                        //상장후최고일         
	char oplistldate                      [ 15];	char _oplistldate;                        //상장후최저일         
	char oplistdate                       [  8];	char _oplistdate;                         //거래개시일           
	char oplastdate                       [  8];	char _oplastdate;                         //최종거래일           
	char hts_rmnn_dynu                    [  4];	char _hts_rmnn_dynu;                      //잔존일               
	char optn_mxpr                        [  9];	char _optn_mxpr;                          //상한가               
	char optn_llam                        [  9];	char _optn_llam;                          //하한가               
	char opgrate                          [  9];	char _opgrate;                            //괴리도               
	char opimpv                           [  5];	char _opimpv;                             //내재변동성           
	char oppastv90                        [  5];	char _oppastv90;                          //과거변동성90         
	char delta                            [  8];	char _delta;                              //델타지수             
	char gama                             [  8];	char _gama;                               //감마지수             
	char vega                             [  8];	char _vega;                               //베가변동성           
	char theta                            [  8];	char _theta;                              //쎄타시간             
	char rho                              [  8];	char _rho;                                //로이자율             
	char opcdratio                        [  6];	char _opcdratio;                          //이자율               
	char opdivideratio                    [  9];	char _opdivideratio;                      //배당액지수           
	char bsop_hour                        [  8];	char _bsop_hour;                          //호가시간             
	char optn_askp1                       [  9];	char _optn_askp1;                         //매도최우선호가       
	char optn_askp2                       [  9];	char _optn_askp2;                         //매도차선호가         
	char optn_askp3                       [  9];	char _optn_askp3;                         //매도차차선호가       
	char optn_askp4                       [  9];	char _optn_askp4;                         //매도4차선호가        
	char optn_askp5                       [  9];	char _optn_askp5;                         //매도5차선호가        
	char optn_bidp1                       [  9];	char _optn_bidp1;                         //매수최우선호가       
	char optn_bidp2                       [  9];	char _optn_bidp2;                         //매수차선호가         
	char optn_bidp3                       [  9];	char _optn_bidp3;                         //매수차차선호가       
	char optn_bidp4                       [  9];	char _optn_bidp4;                         //매수4차선호가        
	char optn_bidp5                       [  9];	char _optn_bidp5;                         //매수5차선호가        
	char askp_rsqn1                       [ 12];	char _askp_rsqn1;                         //매도최우선잔량       
	char askp_rsqn2                       [ 12];	char _askp_rsqn2;                         //매도차선잔량         
	char askp_rsqn3                       [ 12];	char _askp_rsqn3;                         //매도차차선잔량       
	char askp_rsqn4                       [ 12];	char _askp_rsqn4;                         //매도4차선잔량        
	char askp_rsqn5                       [ 12];	char _askp_rsqn5;                         //매도5차선잔량        
	char bidp_rsqn1                       [ 12];	char _bidp_rsqn1;                         //매수최우선잔량       
	char bidp_rsqn2                       [ 12];	char _bidp_rsqn2;                         //매수차선잔량         
	char bidp_rsqn3                       [ 12];	char _bidp_rsqn3;                         //매수차차선잔량       
	char bidp_rsqn4                       [ 12];	char _bidp_rsqn4;                         //매수4차선잔량        
	char bidp_rsqn5                       [ 12];	char _bidp_rsqn5;                         //매수5차선잔량        
	char total_askp_rsqn                  [ 12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn                  [ 12];	char _total_bidp_rsqn;                    //총매수잔량           
	char askp_csnu1                       [ 10];	char _askp_csnu1;                         //매도최우선건수       
	char askp_csnu2                       [ 10];	char _askp_csnu2;                         //매도차선건수         
	char askp_csnu3                       [ 10];	char _askp_csnu3;                         //매도차차선건수       
	char askp_csnu4                       [ 10];	char _askp_csnu4;                         //매도4차선건수        
	char askp_csnu5                       [ 10];	char _askp_csnu5;                         //매도5차선건수        
	char bidp_csnu1                       [ 10];	char _bidp_csnu1;                         //매수최우선건수       
	char bidp_csnu2                       [ 10];	char _bidp_csnu2;                         //매수차선건수         
	char bidp_csnu3                       [ 10];	char _bidp_csnu3;                         //매수차차선건수       
	char bidp_csnu4                       [ 10];	char _bidp_csnu4;                         //매수4차선건수        
	char bidp_csnu5                       [ 10];	char _bidp_csnu5;                         //매수5차선건수        
	char total_askp_csnu                  [ 10];	char _total_askp_csnu;                    //총매도건수           
	char total_bidp_csnu                  [ 10];	char _total_bidp_csnu;                    //총매수건수           
	char opjgubun                         [  8];	char _opjgubun;                           //CB발동여부           
	char opopensign                       [  1];	char _opopensign;                         //시가대비부호         
	char opopenchange                     [  9];	char _opopenchange;                       //시가대비등락         
	char opgratio                         [  5];	char _opgratio;                           //괴리율               
	char optn_prdy_clpr                   [  9];	char _optn_prdy_clpr;                     //전일종가             
	char dynmc_uplmtprc                   [  9];	char _dynmc_uplmtprc;                     //실시간상한가         
	char dynmc_lwlmtprc                   [  9];	char _dynmc_lwlmtprc;                     //실시간하한가         
	char fudynpriceflag                   [  1];	char _fudynpriceflag;                     //동적가격제한여부     
	char dscs_lrqn_vol                    [  8];	char _dscs_lrqn_vol;                      //협의거래량           
	char prc_lmt_mx_step                  [  2];	char _prc_lmt_mx_step;                    //가격제한확대상한단계 
	char prc_lmt_ll_step                  [  2];	char _prc_lmt_ll_step;                    //가격제한확대하한단계 
	char optn_sdpr                        [  9];	char _optn_sdpr;                          //기준가               
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUOREQ03Out1;

typedef struct tagIVWFUOREQ03Out2    //코스피200지수
{
	char fuitem                           [  6];	char _fuitem;                             //코스피200코드        
	char prpr_nmix                        [  9];	char _prpr_nmix;                          //코스피200지수        
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //코스피200등락부호    
	char fuchange                         [  9];	char _fuchange;                           //코스피200등락폭      
	char prdy_ctrt                        [  5];	char _prdy_ctrt;                          //코스피200등락률      
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUOREQ03Out2;

typedef struct tagIVWFUOREQ03Out3    //옵션변동거래량자료, [반복]
{
	char bsop_hour                        [  8];	char _bsop_hour;                          //시간                 
	char optn_prpr                        [  9];	char _optn_prpr;                          //현재가               
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //등락부호             
	char optn_prdy_vrss                   [  9];	char _optn_prdy_vrss;                     //등락폭               
	char optn_askp                        [  9];	char _optn_askp;                          //매도호가             
	char optn_bidp                        [  9];	char _optn_bidp;                          //매수호가             
	char cnqn                             [ 12];	char _cnqn;                               //거래량               
	char acml_vol                         [ 12];	char _acml_vol;                           //누적거래량           
	char ojopenyak                        [ 12];	char _ojopenyak;                          //미결제약정           
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUOREQ03Out3;

typedef struct tagIVWFUOREQ03Out4    //선물최근월물
{
	char fuitem                           [  8];	char _fuitem;                             //선물최근월물코드     
	char fuitemz9                         [  9];	char _fuitemz9;                           //선물최근월물확장코드 
	char fuhname                          [ 12];	char _fuhname;                            //선물최근월물명       
	char fucurr                           [  9];	char _fucurr;                             //선물최근월물지수     
	char fusign                           [  1];	char _fusign;                             //선물최근월물등락부호 
	char fuchange                         [  9];	char _fuchange;                           //선물최근월물등락폭   
	char fuchrate                         [  9];	char _fuchrate;                           //선물최근월물등락률   
	char fuvolall                         [ 12];	char _fuvolall;                           //선물최근월물거래량   
	char acml_tr_pbmn                     [ 18];	char _acml_tr_pbmn;                       //선물최근월물누적거래대금(백만) 
	char bsop_hour                        [  8];	char _bsop_hour;                          //선물최근월물호가시간 
	char futs_askp1                       [  9];	char _futs_askp1;                         //선물최근월물매도최우선호가 
	char futs_askp2                       [  9];	char _futs_askp2;                         //선물최근월물매도차선호가 
	char futs_askp3                       [  9];	char _futs_askp3;                         //선물최근월물매도차차선호가 
	char futs_askp4                       [  9];	char _futs_askp4;                         //선물최근월물매도4차선호가 
	char futs_askp5                       [  9];	char _futs_askp5;                         //선물최근월물매도5차선호가 
	char futs_bidp1                       [  9];	char _futs_bidp1;                         //선물최근월물매수최우선호가 
	char futs_bidp2                       [  9];	char _futs_bidp2;                         //선물최근월물매수차선호가 
	char futs_bidp3                       [  9];	char _futs_bidp3;                         //선물최근월물매수차차선호가 
	char futs_bidp4                       [  9];	char _futs_bidp4;                         //선물최근월물매수4차선호가 
	char futs_bidp5                       [  9];	char _futs_bidp5;                         //선물최근월물매수5차선호가 
	char askp_rsqn1                       [ 12];	char _askp_rsqn1;                         //선물최근월물매도최우선잔량 
	char askp_rsqn2                       [ 12];	char _askp_rsqn2;                         //선물최근월물매도차선잔량 
	char askp_rsqn3                       [ 12];	char _askp_rsqn3;                         //선물최근월물매도차차선잔량 
	char askp_rsqn4                       [ 12];	char _askp_rsqn4;                         //선물최근월물매도4차선잔량 
	char askp_rsqn5                       [ 12];	char _askp_rsqn5;                         //선물최근월물매도5차선잔량 
	char bidp_rsqn1                       [ 12];	char _bidp_rsqn1;                         //선물최근월물매수최우선잔량 
	char bidp_rsqn2                       [ 12];	char _bidp_rsqn2;                         //선물최근월물매수차선잔량 
	char bidp_rsqn3                       [ 12];	char _bidp_rsqn3;                         //선물최근월물매수차차선잔량 
	char bidp_rsqn4                       [ 12];	char _bidp_rsqn4;                         //선물최근월물매수4차선잔량 
	char bidp_rsqn5                       [ 12];	char _bidp_rsqn5;                         //선물최근월물매수5차선잔량 
	char total_askp_rsqn                  [ 12];	char _total_askp_rsqn;                    //선물최근월물총매도잔량 
	char total_bidp_rsqn                  [ 12];	char _total_bidp_rsqn;                    //선물최근월물총매수잔량 
	char askp_csnu1                       [ 10];	char _askp_csnu1;                         //선물최근월물매도최우선건수 
	char askp_csnu2                       [ 10];	char _askp_csnu2;                         //선물최근월물매도차선건수 
	char askp_csnu3                       [ 10];	char _askp_csnu3;                         //선물최근월물매도차차선건수 
	char askp_csnu4                       [ 10];	char _askp_csnu4;                         //선물최근월물매도4차선건수 
	char askp_csnu5                       [ 10];	char _askp_csnu5;                         //선물최근월물매도5차선건수 
	char bidp_csnu1                       [ 10];	char _bidp_csnu1;                         //선물최근월물매수최우선건수 
	char bidp_csnu2                       [ 10];	char _bidp_csnu2;                         //선물최근월물매수차선건수 
	char bidp_csnu3                       [ 10];	char _bidp_csnu3;                         //선물최근월물매수차차선건수 
	char bidp_csnu4                       [ 10];	char _bidp_csnu4;                         //선물최근월물매수4차선건수 
	char bidp_csnu5                       [ 10];	char _bidp_csnu5;                         //선물최근월물매수5차선건수 
	char total_askp_csnu                  [ 10];	char _total_askp_csnu;                    //선물최근월물총매도건수 
	char total_bidp_csnu                  [ 10];	char _total_bidp_csnu;                    //선물최근월물총매수건수 
	char futs_mxpr                        [  9];	char _futs_mxpr;                          //상한가               
	char futs_hgpr                        [  9];	char _futs_hgpr;                          //고가                 
	char futs_oprc                        [  9];	char _futs_oprc;                          //시가                 
	char fuopensign                       [  1];	char _fuopensign;                         //시가대비부호         
	char fuopenchange                     [  9];	char _fuopenchange;                       //시가대비등락         
	char futs_lwpr                        [  9];	char _futs_lwpr;                          //저가                 
	char futs_llam                        [  9];	char _futs_llam;                          //하한가               
	char fupivot2upz5                     [  9];	char _fupivot2upz5;                       //피봇2차저항          
	char fupivot1upz5                     [  9];	char _fupivot1upz5;                       //피봇1차저항          
	char fupivotz5                        [  9];	char _fupivotz5;                          //피봇가               
	char fupivot1dnz5                     [  9];	char _fupivot1dnz5;                       //피봇1차지지          
	char fupivot2dnz5                     [  9];	char _fupivot2dnz5;                       //피봇2차지지          
	char fudynhprice                      [  9];	char _fudynhprice;                        //실시간상한가         
	char fudynlprice                      [  9];	char _fudynlprice;                        //실시간하한가         
	char fudynpriceflag                   [  1];	char _fudynpriceflag;                     //동적가격제한여부     
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUOREQ03Out4;

typedef struct tagIVWFUOREQ03Out5    //선물변동거래량자료, [반복]
{
	char bsop_hour                        [  8];	char _bsop_hour;                          //시간                 
	char futs_prpr                        [  9];	char _futs_prpr;                          //현재가               
	char prdy_vrss_sign                   [  1];	char _prdy_vrss_sign;                     //등락부호             
	char futs_prdy_vrss                   [  9];	char _futs_prdy_vrss;                     //등락폭               
	char futs_askp                        [  9];	char _futs_askp;                          //매도호가             
	char futs_bidp                        [  9];	char _futs_bidp;                          //매수호가             
	char cnqn                             [ 12];	char _cnqn;                               //거래량               
	char acml_vol                         [ 12];	char _acml_vol;                           //누적거래량           
	char ojopenyak                        [ 12];	char _ojopenyak;                          //미결제약정           
	char filler                           [ 30];	char _filler;                             //FILLER               
} TIVWFUOREQ03Out5;

typedef struct tagIVWFUOREQ03Out6    //옵션예상체결
{
	char dongsi                           [  1];	char _dongsi;                             //동시호가구분         
	char jeqprice                         [  9];	char _jeqprice;                           //예상체결가           
	char jeqsign                          [  1];	char _jeqsign;                            //예상체결부호         
	char jeqchange                        [  9];	char _jeqchange;                          //예상체결등락폭       
	char jeqchrate                        [  5];	char _jeqchrate;                          //예상체결등락률       
	char jeqvolume                        [  9];	char _jeqvolume;                          //예상체결수량         //파생시장제도개선(2024.03.14)
	char filler                           [ 21];	char _filler;                             //FILLER               //필러(30->21)
} TIVWFUOREQ03Out6;

typedef struct tagIVWFUOREQ03Out7    //선물예상체결
{
	char dongsi                           [  1];	char _dongsi;                             //동시호가구분         
	char jeqprice                         [  9];	char _jeqprice;                           //예상체결가           
	char jeqsign                          [  1];	char _jeqsign;                            //예상체결부호         
	char jeqchange                        [  9];	char _jeqchange;                          //예상체결등락폭       
	char jeqchrate                        [  5];	char _jeqchrate;                          //예상체결등락률       
	char jeqvolume                        [  9];	char _jeqvolume;                          //예상체결수량         //파생시장제도개선(2024.03.14)
	char filler                           [ 21];	char _filler;                             //FILLER               //필러(30->21)
} TIVWFUOREQ03Out7;

typedef struct tagIVWFUOREQ03
{
	TIVWFUOREQ03In                    ivwfuoreq03in                         ;  //기본입력 
	TIVWFUOREQ03Out1                  ivwfuoreq03out1                       ;  //종목마스타기본자료 
	TIVWFUOREQ03Out2                  ivwfuoreq03out2                       ;  //코스피200지수 
	TIVWFUOREQ03Out3                  ivwfuoreq03out3                  [ 20];  //옵션변동거래량자료 , [반복]
	TIVWFUOREQ03Out4                  ivwfuoreq03out4                       ;  //선물최근월물 
	TIVWFUOREQ03Out5                  ivwfuoreq03out5                  [ 20];  //선물변동거래량자료 , [반복]
	TIVWFUOREQ03Out6                  ivwfuoreq03out6                       ;  //옵션예상체결 
	TIVWFUOREQ03Out7                  ivwfuoreq03out7                       ;  //선물예상체결 
} TIVWFUOREQ03;

typedef struct tagIVWJFUMST01In    //기본입력
{
	char formlang[1];	char _formlang;                           //한영구분             /*k:KOREANe:ENGLISH*/
	char shrn_iscd[9];	char _shrn_iscd;                          //종목코드             
} TIVWJFUMST01In;

typedef struct tagIVWJFUMST01Out1    //주식선물MASTER기본자료
{
	char shrn_iscd[8];	char _shrn_iscd;                          //종목코드             
	char ftop_kor_isnm[50];	char _ftop_kor_isnm;                      //한글명               
	char ftop_eng_isnm[50];	char _ftop_eng_isnm;                      //영문명               
	char futs_sdpr[7];	char _futs_sdpr;                          //기준가격             
	char futs_mxpr[7];	char _futs_mxpr;                          //상한가               
	char futs_llam[7];	char _futs_llam;                          //하한가               
	char futs_prdy_clpr[7];	char _futs_prdy_clpr;                     //전일종가             
	char futs_tr_unit[16];	char _futs_tr_unit;                       //거래단위             
	char openyak[12];	char _openyak;                            //미결제약정수량       
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //전일대비부호         
	char futs_prdy_vrss[7];	char _futs_prdy_vrss;                     //전일대비             
	char futs_prpr[7];	char _futs_prpr;                          //현재가               
	char futs_oprc[7];	char _futs_oprc;                          //시가                 
	char futs_hgpr[7];	char _futs_hgpr;                          //고가                 
	char futs_lwpr[7];	char _futs_lwpr;                          //저가                 
	char acml_vol[12];	char _acml_vol;                           //누적체결수량(계약)   
	char spead_acml_vol[12];	char _spead_acml_vol;                     //스프레드체결수량     
	char acml_tr_pbmn[12];	char _acml_tr_pbmn;                       //누적거래대금(천원)   
	char bsop_hour[8];	char _bsop_hour;                          //호가시간             
	char futs_askp1[7];	char _futs_askp1;                         //매도우선호가         
	char futs_bidp1[7];	char _futs_bidp1;                         //매수우선호가         
	char askp_rsqn1[12];	char _askp_rsqn1;                         //매도잔량             
	char bidp_rsqn1[12];	char _bidp_rsqn1;                         //매수잔량             
	char futs_askp2[7];	char _futs_askp2;                         //매도2차호가          
	char futs_bidp2[7];	char _futs_bidp2;                         //매수2차호가          
	char askp_rsqn2[12];	char _askp_rsqn2;                         //매도2차잔량          
	char bidp_rsqn2[12];	char _bidp_rsqn2;                         //매수2차잔량          
	char futs_askp3[7];	char _futs_askp3;                         //매도3차호가          
	char futs_bidp3[7];	char _futs_bidp3;                         //매수3차호가          
	char askp_rsqn3[12];	char _askp_rsqn3;                         //매도3차잔량          
	char bidp_rsqn3[12];	char _bidp_rsqn3;                         //매수3차잔량          
	char futs_askp4[7];	char _futs_askp4;                         //매도4차호가          
	char futs_bidp4[7];	char _futs_bidp4;                         //매수4차호가          
	char askp_rsqn4[12];	char _askp_rsqn4;                         //매도4차잔량          
	char bidp_rsqn4[12];	char _bidp_rsqn4;                         //매수4차잔량          
	char futs_askp5[7];	char _futs_askp5;                         //매도5차호가          
	char futs_bidp5[7];	char _futs_bidp5;                         //매수5차호가          
	char askp_rsqn5[12];	char _askp_rsqn5;                         //매도5차잔량          
	char bidp_rsqn5[12];	char _bidp_rsqn5;                         //매수5차잔량          
	char futs_askp6[7];	char _futs_askp6;                         //매도6차호가          
	char futs_bidp6[7];	char _futs_bidp6;                         //매수6차호가          
	char askp_rsqn6[12];	char _askp_rsqn6;                         //매도6차잔량          
	char bidp_rsqn6[12];	char _bidp_rsqn6;                         //매수6차잔량          
	char futs_askp7[7];	char _futs_askp7;                         //매도7차호가          
	char futs_bidp7[7];	char _futs_bidp7;                         //매수7차호가          
	char askp_rsqn7[12];	char _askp_rsqn7;                         //매도7차잔량          
	char bidp_rsqn7[12];	char _bidp_rsqn7;                         //매수7차잔량          
	char futs_askp8[7];	char _futs_askp8;                         //매도8차호가          
	char futs_bidp8[7];	char _futs_bidp8;                         //매수8차호가          
	char askp_rsqn8[12];	char _askp_rsqn8;                         //매도8차잔량          
	char bidp_rsqn8[12];	char _bidp_rsqn8;                         //매수8차잔량          
	char futs_askp9[7];	char _futs_askp9;                         //매도9차호가          
	char futs_bidp9[7];	char _futs_bidp9;                         //매수9차호가          
	char askp_rsqn9[12];	char _askp_rsqn9;                         //매도9차잔량          
	char bidp_rsqn9[12];	char _bidp_rsqn9;                         //매수9차잔량          
	char futs_askp10[7];	char _futs_askp10;                        //매도10차호가         
	char futs_bidp10[7];	char _futs_bidp10;                        //매수10차호가         
	char askp_rsqn10[12];	char _askp_rsqn10;                        //매도10차잔량         
	char bidp_rsqn10[12];	char _bidp_rsqn10;                        //매수10차잔량         
	char askp_csnu1[10];	char _askp_csnu1;                         //매도건수             
	char bidp_csnu1[10];	char _bidp_csnu1;                         //매수건수             
	char askp_csnu2[10];	char _askp_csnu2;                         //매도2차건수          
	char bidp_csnu2[10];	char _bidp_csnu2;                         //매수2차건수          
	char askp_csnu3[10];	char _askp_csnu3;                         //매도3차건수          
	char bidp_csnu3[10];	char _bidp_csnu3;                         //매수3차건수          
	char askp_csnu4[10];	char _askp_csnu4;                         //매도4차건수          
	char bidp_csnu4[10];	char _bidp_csnu4;                         //매수4차건수          
	char askp_csnu5[10];	char _askp_csnu5;                         //매도5차건수          
	char bidp_csnu5[10];	char _bidp_csnu5;                         //매수5차건수          
	char askp_csnu6[10];	char _askp_csnu6;                         //매도6차건수          
	char bidp_csnu6[10];	char _bidp_csnu6;                         //매수6차건수          
	char askp_csnu7[10];	char _askp_csnu7;                         //매도7차건수          
	char bidp_csnu7[10];	char _bidp_csnu7;                         //매수7차건수          
	char askp_csnu8[10];	char _askp_csnu8;                         //매도8차건수          
	char bidp_csnu8[10];	char _bidp_csnu8;                         //매수8차건수          
	char askp_csnu9[10];	char _askp_csnu9;                         //매도9차건수          
	char bidp_csnu9[10];	char _bidp_csnu9;                         //매수9차건수          
	char askp_csnu10[10];	char _askp_csnu10;                        //매도10차건수         
	char bidp_csnu10[10];	char _bidp_csnu10;                        //매수10차건수         
	char total_askp_rsqn[12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn[12];	char _total_bidp_rsqn;                    //총매수잔량           
	char total_askp_csnu[10];	char _total_askp_csnu;                    //총매도건수           
	char total_bidp_csnu[10];	char _total_bidp_csnu;                    //총매수건수           
	char hts_thpr[7];	char _hts_thpr;                           //이론가               
	char futs_prdy_ctrt[5];	char _futs_prdy_ctrt;                     //등락률               
	char fupivot2upz5[7];	char _fupivot2upz5;                       //피봇2차저항          
	char fupivot1upz5[7];	char _fupivot1upz5;                       //피봇1차저항          
	char fupivotz5[7];	char _fupivotz5;                          //피봇가               
	char fupivot1dnz5[7];	char _fupivot1dnz5;                       //피봇1차지지          
	char fupivot2dnz5[7];	char _fupivot2dnz5;                       //피봇2차지지          
	char mrkt_basis[7];	char _mrkt_basis;                         //베이시스             
	char fugrate[7];	char _fugrate;                            //괴리도               
	char fugratio[6];	char _fugratio;                           //괴리율               
	char fupreopenyak[7];	char _fupreopenyak;                       //미결제약정전일       /*미결제약정전일대비증감*/
	char fulisthprice[7];	char _fulisthprice;                       //상장후최고가         
	char fulisthdate[8];	char _fulisthdate;                        //상장후최고일         
	char fulistlprice[7];	char _fulistlprice;                       //상장후최저가         
	char fulistldate[8];	char _fulistldate;                        //상장후최저일         
	char fulastdate[8];	char _fulastdate;                         //최종거래일           
	char hts_rmnn_dynu[3];	char _hts_rmnn_dynu;                      //잔존일               
	char cd_mnrt[6];	char _cd_mnrt;                            //무위험이자율         
	char fuopenchange[7];	char _fuopenchange;                       //시가대비등락         
	char dynmc_uplmtprc[7];	char _dynmc_uplmtprc;                     //실시간상한가         
	char dynmc_lwlmtprc[7];	char _dynmc_lwlmtprc;                     //실시간하한가         
	char fudynpriceflag[1];	char _fudynpriceflag;                     //동적가격제한여부     
	char prc_lmt_exlmtgb[1];	char _prc_lmt_exlmtgb;                    //가격확대예정구분     
	char prc_lmt_mx_step[1];	char _prc_lmt_mx_step;                    //가격제한확대상한단계 
	char prc_lmt_ll_step[1];	char _prc_lmt_ll_step;                    //가격제한확대하한단계 
	char filler[30];	char _filler;                             //FILLER               
} TIVWJFUMST01Out1;

typedef struct tagIVWJFUMST01Out2    //기초자산
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             
	char hts_kor_isnm[20];	char _hts_kor_isnm;                       //종목명               
	char stck_prpr[7];	char _stck_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[6];	char _prdy_vrss;                          //등락폭               
	char flng_code[16];	char _flng_code;                          //락구분               
	char prdy_ctrt[5];	char _prdy_ctrt;                          //등락률               
	char cntg_askp[7];	char _cntg_askp;                          //매도호가             
	char cntg_bidp[7];	char _cntg_bidp;                          //매수호가             
	char acml_vol[12];	char _acml_vol;                           //거래량               
	char volrate[6];	char _volrate;                            //거래비율             
	char stck_mxpr[7];	char _stck_mxpr;                          //상한가               
	char stck_hgpr[7];	char _stck_hgpr;                          //고가                 
	char stck_oprc[7];	char _stck_oprc;                          //시가                 
	char stck_lwpr[7];	char _stck_lwpr;                          //저가                 
	char stck_llam[7];	char _stck_llam;                          //하한가               
	char new_volumez12[12];	char _new_volumez12;                      //신규거래량           
	char filler[30];	char _filler;                             //FILLER               
} TIVWJFUMST01Out2;

typedef struct tagIVWJFUMST01Out3    //주식선물예상체결
{
	char dongsi[1];	char _dongsi;                             //동시호가구분         
	char futs_antc_cnpr[7];	char _futs_antc_cnpr;                     //예상체결가           
	char jeqsign[1];	char _jeqsign;                            //예상체결부호         
	char rgbf_antc_vrss[7];	char _rgbf_antc_vrss;                     //예상체결등락폭       
	char rgbf_antc_ctrt[5];	char _rgbf_antc_ctrt;                     //예상체결등락률       
	char antc_cnqn[9];	char _antc_cnqn;                          //예상체결수량         //파생시장제도개선(2024.03.14)
	char filler[21];	char _filler;                             //FILLER               //필러(30->21)
} TIVWJFUMST01Out3;

typedef struct tagIVWJFUMST01
{
	TIVWJFUMST01In                    ivwjfumst01in;  //기본입력 
	TIVWJFUMST01Out1                  ivwjfumst01out1;  //주식선물MASTER기본자료 
	TIVWJFUMST01Out2                  ivwjfumst01out2;  //기초자산 
	TIVWJFUMST01Out3                  ivwjfumst01out3;  //주식선물예상체결 
} TIVWJFUMST01;

typedef struct tagIVWJFUMST02In    //입력데이타
{
	char shrn_iscd[9];	char _shrn_iscd;                          //입력코드             
} TIVWJFUMST02In;

typedef struct tagIVWJFUMST02Out1    //IVWJFUMST02OutUnder
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             
	char hts_kor_isnm[20];	char _hts_kor_isnm;                       //종목명               
	char stck_prpr[7];	char _stck_prpr;                          //지수                 
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //전일비부호           
	char prdy_vrss[6];	char _prdy_vrss;                          //전일비               
	char filler[30];	char _filler;                             //FILLER               
} TIVWJFUMST02Out1;

typedef struct tagIVWJFUMST02Out2    //IVWJFUMST02OutSMaster
{
	char shrn_iscd[8];	char _shrn_iscd;                          //종목코드             
	char futs_prpr[8];	char _futs_prpr;                          //지수                 
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //전일비부호           
	char futs_prdy_vrss[7];	char _futs_prdy_vrss;                     //전일비               
	char futs_prdy_ctrt[5];	char _futs_prdy_ctrt;                     //등락률               
	char futs_oprc[7];	char _futs_oprc;                          //시가                 
	char futs_hgpr[7];	char _futs_hgpr;                          //고가                 
	char futs_lwpr[7];	char _futs_lwpr;                          //저가                 
	char acml_vol[12];	char _acml_vol;                           //거래량               
	char acml_tr_pbmn[18];	char _acml_tr_pbmn;                       //누적거래대금(천원)   
	char fuspcurr1[7];	char _fuspcurr1;                          //의제약정가(근월물)   
	char fuspcurr2[7];	char _fuspcurr2;                          //의제약정가(원월물)   
	char shrn_iscd1[8];	char _shrn_iscd1;                         //종목코드(근월물)     
	char shrn_iscd2[8];	char _shrn_iscd2;                         //종목코드(원월물)     
	char dynmc_uplmtprc[7];	char _dynmc_uplmtprc;                     //실시간상한가         
	char dynmc_lwlmtprc[7];	char _dynmc_lwlmtprc;                     //실시간하한가         
	char fudynpriceflag[1];	char _fudynpriceflag;                     //동적가격제한여부     
	char filler[30];	char _filler;                             //FILLER               
} TIVWJFUMST02Out2;

typedef struct tagIVWJFUMST02Out3    //주식선물호가3
{
	char shrn_iscd[8];	char _shrn_iscd;                          //종목코드             
	char ftop_kor_isnm[50];	char _ftop_kor_isnm;                      //한글명               
	char bsop_hour[8];	char _bsop_hour;                          //호가시간             
	char futs_askp1[8];	char _futs_askp1;                         //매도우선호가         
	char futs_bidp1[8];	char _futs_bidp1;                         //매수우선호가         
	char askp_rsqn1[12];	char _askp_rsqn1;                         //매도잔량             
	char bidp_rsqn1[12];	char _bidp_rsqn1;                         //매수잔량             
	char futs_askp2[8];	char _futs_askp2;                         //2차매도호가          
	char futs_bidp2[8];	char _futs_bidp2;                         //2차매수호가          
	char askp_rsqn2[12];	char _askp_rsqn2;                         //2차매도잔량          
	char bidp_rsqn2[12];	char _bidp_rsqn2;                         //2차매수잔량          
	char futs_askp3[8];	char _futs_askp3;                         //3차매도호가          
	char futs_bidp3[8];	char _futs_bidp3;                         //3차매수호가          
	char askp_rsqn3[12];	char _askp_rsqn3;                         //3차매도잔량          
	char bidp_rsqn3[12];	char _bidp_rsqn3;                         //3차매수잔량          
	char futs_askp4[8];	char _futs_askp4;                         //4차매도호가          
	char futs_bidp4[8];	char _futs_bidp4;                         //4차매수호가          
	char askp_rsqn4[12];	char _askp_rsqn4;                         //4차매도잔량          
	char bidp_rsqn4[12];	char _bidp_rsqn4;                         //4차매수잔량          
	char futs_askp5[8];	char _futs_askp5;                         //5차매도호가          
	char futs_bidp5[8];	char _futs_bidp5;                         //5차매수호가          
	char askp_rsqn5[12];	char _askp_rsqn5;                         //5차매도잔량          
	char bidp_rsqn5[12];	char _bidp_rsqn5;                         //5차매수잔량          
	char futs_askp6[8];	char _futs_askp6;                         //6차매도호가          
	char futs_bidp6[8];	char _futs_bidp6;                         //6차매수호가          
	char askp_rsqn6[12];	char _askp_rsqn6;                         //6차매도잔량          
	char bidp_rsqn6[12];	char _bidp_rsqn6;                         //6차매수잔량          
	char futs_askp7[8];	char _futs_askp7;                         //7차매도호가          
	char futs_bidp7[8];	char _futs_bidp7;                         //7차매수호가          
	char askp_rsqn7[12];	char _askp_rsqn7;                         //7차매도잔량          
	char bidp_rsqn7[12];	char _bidp_rsqn7;                         //7차매수잔량          
	char futs_askp8[8];	char _futs_askp8;                         //8차매도호가          
	char futs_bidp8[8];	char _futs_bidp8;                         //8차매수호가          
	char askp_rsqn8[12];	char _askp_rsqn8;                         //8차매도잔량          
	char bidp_rsqn8[12];	char _bidp_rsqn8;                         //8차매수잔량          
	char futs_askp9[8];	char _futs_askp9;                         //9차매도호가          
	char futs_bidp9[8];	char _futs_bidp9;                         //9차매수호가          
	char askp_rsqn9[12];	char _askp_rsqn9;                         //9차매도잔량          
	char bidp_rsqn9[12];	char _bidp_rsqn9;                         //9차매수잔량          
	char futs_askp10[8];	char _futs_askp10;                        //10차매도호가         
	char futs_bidp10[8];	char _futs_bidp10;                        //10차매수호가         
	char askp_rsqn10[12];	char _askp_rsqn10;                        //10차매도잔량         
	char bidp_rsqn10[12];	char _bidp_rsqn10;                        //10차매수잔량         
	char askp_csnu1[10];	char _askp_csnu1;                         //매도건수             
	char bidp_csnu1[10];	char _bidp_csnu1;                         //매수건수             
	char askp_csnu2[10];	char _askp_csnu2;                         //2차매도건수          
	char bidp_csnu2[10];	char _bidp_csnu2;                         //2차매수건수          
	char askp_csnu3[10];	char _askp_csnu3;                         //3차매도건수          
	char bidp_csnu3[10];	char _bidp_csnu3;                         //3차매수건수          
	char askp_csnu4[10];	char _askp_csnu4;                         //4차매도건수          
	char bidp_csnu4[10];	char _bidp_csnu4;                         //4차매수건수          
	char askp_csnu5[10];	char _askp_csnu5;                         //5차매도건수          
	char bidp_csnu5[10];	char _bidp_csnu5;                         //5차매수건수          
	char askp_csnu6[10];	char _askp_csnu6;                         //6차매도건수          
	char bidp_csnu6[10];	char _bidp_csnu6;                         //6차매수건수          
	char askp_csnu7[10];	char _askp_csnu7;                         //7차매도건수          
	char bidp_csnu7[10];	char _bidp_csnu7;                         //7차매수건수          
	char askp_csnu8[10];	char _askp_csnu8;                         //8차매도건수          
	char bidp_csnu8[10];	char _bidp_csnu8;                         //8차매수건수          
	char askp_csnu9[10];	char _askp_csnu9;                         //9차매도건수          
	char bidp_csnu9[10];	char _bidp_csnu9;                         //9차매수건수          
	char askp_csnu10[10];	char _askp_csnu10;                        //10차매도건수         
	char bidp_csnu10[10];	char _bidp_csnu10;                        //10차매수건수         
	char total_askp_rsqn[12];	char _total_askp_rsqn;                    //총매도잔량           
	char total_bidp_rsqn[12];	char _total_bidp_rsqn;                    //총매수잔량           
	char total_askp_csnu[10];	char _total_askp_csnu;                    //총매도건수           
	char total_bidp_csnu[10];	char _total_bidp_csnu;                    //총매수건수           
	char undershcode[6];	char _undershcode;                        //기초자산종목코드     
	char underhname[20];	char _underhname;                         //기초자산종목명       
	char eitem[2];	char _eitem;                              //기초대상주식         
	char bp_jgubun[1];	char _bp_jgubun;                          //BP용장구분           
	char filler[30];	char _filler;                             //FILLER               
} TIVWJFUMST02Out3;

typedef struct tagIVWJFUMST02Out4    //선물SPREAD
{
	char thspread[7];	char _thspread;                           //이론스프레드         
	char respread[7];	char _respread;                           //실제스프레드         
	char fugrate1[7];	char _fugrate1;                           //괴리                 
	char filler[30];	char _filler;                             //FILLER               
} TIVWJFUMST02Out4;

typedef struct tagIVWJFUMST02
{
	TIVWJFUMST02In                    ivwjfumst02in;  //입력데이타 
	TIVWJFUMST02Out1                  ivwjfumst02out1;  //IVWJFUMST02OutUnder 
	TIVWJFUMST02Out2                  ivwjfumst02out2;  //IVWJFUMST02OutSMaster 
	TIVWJFUMST02Out3                  ivwjfumst02out3;  //주식선물호가3 
	TIVWJFUMST02Out4                  ivwjfumst02out4;  //선물SPREAD 
} TIVWJFUMST02;

typedef struct tagIVWELWREQ01In    //기본입력
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             
} TIVWELWREQ01In;

typedef struct tagIVWELWREQ01Out1    //종목마스타기본자료
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             
	char hts_kor_isnm[40];	char _hts_kor_isnm;                       //종목명               
	char stck_prpr[10];	char _stck_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[10];	char _prdy_vrss;                          //등락폭               
	char prdy_ctrt[5];	char _prdy_ctrt;                          //등락률               
	char askp[10];	char _askp;                               //매도호가             
	char bidp[10];	char _bidp;                               //매수호가             
	char acml_vol[12];	char _acml_vol;                           //거래량               
	char acml_rate[6];	char _acml_rate;                          //거래비율             
	char acml_tr_pbmn[12];	char _acml_tr_pbmn;                       //거래대금             
	char stck_oprc[10];	char _stck_oprc;                          //시가                 
	char stck_hgpr[10];	char _stck_hgpr;                          //고가                 
	char stck_lwpr[10];	char _stck_lwpr;                          //저가                 
	char stck_pblc_prc[10];	char _stck_pblc_prc;                      //발행가               
	char stck_llam[10];	char _stck_llam;                          //하한가               
	char hts_thpr[10];	char _hts_thpr;                           //이론가               
	char dprt_val[10];	char _dprt_val;                           //괴리도               
	char acpr[10];	char _acpr;                               //행사가               
	char dryy_hgpr[10];	char _dryy_hgpr;                          //상장후최고가         
	char dryy_hgpr_date[4];	char _dryy_hgpr_date;                     //상장후최고가일       
	char dryy_lwpr[10];	char _dryy_lwpr;                          //상장후최저가         
	char dryy_lwpr_date[4];	char _dryy_lwpr_date;                     //상장후최저가일       
	char prdy_clpr[10];	char _prdy_clpr;                          //전일종가             
	char bsop_hour[8];	char _bsop_hour;                          //호가시간             
	char askp1[10];	char _askp1;                              //매도1호가            
	char askp2[10];	char _askp2;                              //매도2호가            
	char askp3[10];	char _askp3;                              //매도3호가            
	char askp4[10];	char _askp4;                              //매도4호가            
	char askp5[10];	char _askp5;                              //매도5호가            
	char askp6[10];	char _askp6;                              //매도6호가            
	char askp7[10];	char _askp7;                              //매도7호가            
	char askp8[10];	char _askp8;                              //매도8호가            
	char askp9[10];	char _askp9;                              //매도9호가            
	char askp10[10];	char _askp10;                             //매도10호가           
	char bidp1[10];	char _bidp1;                              //매수1호가            
	char bidp2[10];	char _bidp2;                              //매수2호가            
	char bidp3[10];	char _bidp3;                              //매수3호가            
	char bidp4[10];	char _bidp4;                              //매수4호가            
	char bidp5[10];	char _bidp5;                              //매수5호가            
	char bidp6[10];	char _bidp6;                              //매수6호가            
	char bidp7[10];	char _bidp7;                              //매수7호가            
	char bidp8[10];	char _bidp8;                              //매수8호가            
	char bidp9[10];	char _bidp9;                              //매수9호가            
	char bidp10[10];	char _bidp10;                             //매수10호가           
	char askp_rsqn1[12];	char _askp_rsqn1;                         //매도1호가잔량        
	char askp_rsqn2[12];	char _askp_rsqn2;                         //매도2호가잔량        
	char askp_rsqn3[12];	char _askp_rsqn3;                         //매도3호가잔량        
	char askp_rsqn4[12];	char _askp_rsqn4;                         //매도4호가잔량        
	char askp_rsqn5[12];	char _askp_rsqn5;                         //매도5호가잔량        
	char askp_rsqn6[12];	char _askp_rsqn6;                         //매도6호가잔량        
	char askp_rsqn7[12];	char _askp_rsqn7;                         //매도7호가잔량        
	char askp_rsqn8[12];	char _askp_rsqn8;                         //매도8호가잔량        
	char askp_rsqn9[12];	char _askp_rsqn9;                         //매도9호가잔량        
	char askp_rsqn10[12];	char _askp_rsqn10;                        //매도10호가잔량       
	char bidp_rsqn1[12];	char _bidp_rsqn1;                         //매수1호가잔량        
	char bidp_rsqn2[12];	char _bidp_rsqn2;                         //매수2호가잔량        
	char bidp_rsqn3[12];	char _bidp_rsqn3;                         //매수3호가잔량        
	char bidp_rsqn4[12];	char _bidp_rsqn4;                         //매수4호가잔량        
	char bidp_rsqn5[12];	char _bidp_rsqn5;                         //매수5호가잔량        
	char bidp_rsqn6[12];	char _bidp_rsqn6;                         //매수6호가잔량        
	char bidp_rsqn7[12];	char _bidp_rsqn7;                         //매수7호가잔량        
	char bidp_rsqn8[12];	char _bidp_rsqn8;                         //매수8호가잔량        
	char bidp_rsqn9[12];	char _bidp_rsqn9;                         //매수9호가잔량        
	char bidp_rsqn10[12];	char _bidp_rsqn10;                        //매수10호가잔량       
	char lp_askp_rsqn1[12];	char _lp_askp_rsqn1;                      //LP매도1호가잔량      
	char lp_askp_rsqn2[12];	char _lp_askp_rsqn2;                      //LP매도2호가잔량      
	char lp_askp_rsqn3[12];	char _lp_askp_rsqn3;                      //LP매도3호가잔량      
	char lp_askp_rsqn4[12];	char _lp_askp_rsqn4;                      //LP매도4호가잔량      
	char lp_askp_rsqn5[12];	char _lp_askp_rsqn5;                      //LP매도5호가잔량      
	char lp_askp_rsqn6[12];	char _lp_askp_rsqn6;                      //LP매도6호가잔량      
	char lp_askp_rsqn7[12];	char _lp_askp_rsqn7;                      //LP매도7호가잔량      
	char lp_askp_rsqn8[12];	char _lp_askp_rsqn8;                      //LP매도8호가잔량      
	char lp_askp_rsqn9[12];	char _lp_askp_rsqn9;                      //LP매도9호가잔량      
	char lp_askp_rsqn10[12];	char _lp_askp_rsqn10;                     //LP매도10호가잔량     
	char lp_bidp_rsqn1[12];	char _lp_bidp_rsqn1;                      //LP매수1호가잔량      
	char lp_bidp_rsqn2[12];	char _lp_bidp_rsqn2;                      //LP매수2호가잔량      
	char lp_bidp_rsqn3[12];	char _lp_bidp_rsqn3;                      //LP매수3호가잔량      
	char lp_bidp_rsqn4[12];	char _lp_bidp_rsqn4;                      //LP매수4호가잔량      
	char lp_bidp_rsqn5[12];	char _lp_bidp_rsqn5;                      //LP매수5호가잔량      
	char lp_bidp_rsqn6[12];	char _lp_bidp_rsqn6;                      //LP매수6호가잔량      
	char lp_bidp_rsqn7[12];	char _lp_bidp_rsqn7;                      //LP매수7호가잔량      
	char lp_bidp_rsqn8[12];	char _lp_bidp_rsqn8;                      //LP매수8호가잔량      
	char lp_bidp_rsqn9[12];	char _lp_bidp_rsqn9;                      //LP매수9호가잔량      
	char lp_bidp_rsqn10[12];	char _lp_bidp_rsqn10;                     //LP매수10호가잔량     
	char total_askp_rsqn[12];	char _total_askp_rsqn;                    //총매도호가잔량       
	char total_bidp_rsqn[12];	char _total_bidp_rsqn;                    //총매수호가잔량       
	char hts_ints_vltl[10];	char _hts_ints_vltl;                      //내재변동성           
	char delta[9];	char _delta;                              //델타                 
	char gama[9];	char _gama;                               //감마                 
	char vega[9];	char _vega;                               //베가                 
	char theta[9];	char _theta;                              //세타                 
	char rho[9];	char _rho;                                //로우                 
	char cd_mnrt[6];	char _cd_mnrt;                            //이자율               
	char divide_ratio[9];	char _divide_ratio;                       //배당액지수           
	char hts_rmnn_dynu[4];	char _hts_rmnn_dynu;                      //잔존일               
	char prd_begn_date[8];	char _prd_begn_date;                      //행사기간개시일       
	char prd_fin_date[8];	char _prd_fin_date;                       //행사기간종료일       
	char last_tr_date[8];	char _last_tr_date;                       //최종거래일           
	char istu_name[50];	char _istu_name;                          //발행기관             
	char lstn_stcn[12];	char _lstn_stcn;                          //발행수량             
	char rght_cls_code[4];	char _rght_cls_code;                      //권리유형             
	char evnt_cls_code[6];	char _evnt_cls_code;                      //권리행사방식         
	char stlm_cls_code[9];	char _stlm_cls_code;                      //결제방법             
	char cnvr_rate[8];	char _cnvr_rate;                          //전환비율             
	char cmps_rate[5];	char _cmps_rate;                          //최소지급율           
	char prc_asrt[5];	char _prc_asrt;                           //가격상승참여율       
	char paym_date[8];	char _paym_date;                          //최종지급일           
	char lp_oder_able_yn[4];	char _lp_oder_able_yn;                    //LP주문가능여부       
	char prit[8];	char _prit;                               //패리티               
	char gear[8];	char _gear;                               //기어링비율           
	char prls_qryr_rate[8];	char _prls_qryr_rate;                     //손익분기율           
	char cfp[8];	char _cfp;                                //자본지지점           
	char lp_name1[6];	char _lp_name1;                           //LP회원사1            
	char lp_name2[6];	char _lp_name2;                           //LP회원사2            
	char lp_name3[6];	char _lp_name3;                           //LP회원사3            
	char lp_name4[6];	char _lp_name4;                           //LP회원사4            
	char lp_name5[6];	char _lp_name5;                           //LP회원사5            
	char aspr_cls_code[1];	char _aspr_cls_code;                      //동시호가구분         
	char antc_cnpr[10];	char _antc_cnpr;                          //예상체결가           
	char antc_sign[1];	char _antc_sign;                          //예상체결부호         
	char antc_vrss[10];	char _antc_vrss;                          //예상체결등락폭       
	char antc_ctrt[5];	char _antc_ctrt;                          //예상체결등락률       
	char antc_vol[12];	char _antc_vol;                           //예상체결수량         
	char lp_hvol[12];	char _lp_hvol;                            //LP보유수량           
	char lp_rate[5];	char _lp_rate;                            //LP보유율             
	char e_gear[8];	char _e_gear;                             //E기어링              
	char ccls_paym_prc[8];	char _ccls_paym_prc;                      //확정지급액           
	char lstn_date[8];	char _lstn_date;                          //상장일               
	char listh_date[8];	char _listh_date;                         //상장후최고가일       
	char listl_date[8];	char _listl_date;                         //상장후최저가일       
	char ints_wrth[8];	char _ints_wrth;                          //내재가치             
	char lvrg_val[8];	char _lvrg_val;                           //레버리지             
	char time_wrth[10];	char _time_wrth;                          //시간가치             
	char dprt[6];	char _dprt;                               //괴리율               
	char prls_qryr_rate1[10];	char _prls_qryr_rate1;                    //손익분기점(정수)     
	char paym_pxpr_name[50];	char _paym_pxpr_name;                     //지급대리인           
	char optn_cls_code[2];	char _optn_cls_code;                      //종목구분             /*01:표준,03:조기종료*/
	char ko_vltn_prc[6];	char _ko_vltn_prc;                        //조기종료가           
	char apprch_rate[5];	char _apprch_rate;                        //KO접근도             
	char stnd_iscd[12];	char _stnd_iscd;                          //확장코드             
	char min_payment[8];	char _min_payment;                        //최소지급액           
	char trht_yn[1];	char _trht_yn;                            //거래정지구분         
	char dprt2[8];	char _dprt2;                              //괴리율2              
	char lp_stop[8];	char _lp_stop;                            //LP종료일             
	char gonggb[1];	char _gonggb;                             //추가상장공시         
	char lp_impv[5];	char _lp_impv;                            //LP내재변동성         
	char r_intval[8];	char _r_intval;                           //실시간용내재가치     
	char profit_pt2[10];	char _profit_pt2;                         //손익분기점(소수점)   
	char alrm_cls_code[1];	char _alrm_cls_code;                      //투자주의구분         
} TIVWELWREQ01Out1;

typedef struct tagIVWELWREQ01Out2    //기초자산정보
{
	char code1[6];	char _code1;                              //기초자산코드1        
	char hname1[40];	char _hname1;                             //기초자산명1          
	char price1[10];	char _price1;                             //현재가1              
	char sign1[1];	char _sign1;                              //등락부호1            
	char change1[10];	char _change1;                            //등락폭1              
	char chrate1[5];	char _chrate1;                            //등락률1              
	char comrate1[5];	char _comrate1;                           //구성비1              
	char pastv1[5];	char _pastv1;                             //과거변동성1          
	char basegubun[1];	char _basegubun;                          //기초자산시장구분     /*1:코스피,2:코스닥*/
} TIVWELWREQ01Out2;

typedef struct tagIVWELWREQ01Out3    //거래원정보
{
	char bsop_hour[5];	char _bsop_hour;                          //시간                 
	char off_tra1[6];	char _off_tra1;                           //매도거래원1          
	char bid_tra1[6];	char _bid_tra1;                           //매수거래원1          
	char off_volume1[12];	char _off_volume1;                        //매도거래량1          
	char bid_volume1[12];	char _bid_volume1;                        //매수거래량1          
	char off_tra2[6];	char _off_tra2;                           //매도거래원2          
	char bid_tra2[6];	char _bid_tra2;                           //매수거래원2          
	char off_volume2[12];	char _off_volume2;                        //매도거래량2          
	char bid_volume2[12];	char _bid_volume2;                        //매수거래량2          
	char off_tra3[6];	char _off_tra3;                           //매도거래원3          
	char bid_tra3[6];	char _bid_tra3;                           //매수거래원3          
	char off_volume3[12];	char _off_volume3;                        //매도거래량3          
	char bid_volume3[12];	char _bid_volume3;                        //매수거래량3          
	char off_tra4[6];	char _off_tra4;                           //매도거래원4          
	char bid_tra4[6];	char _bid_tra4;                           //매수거래원4          
	char off_volume4[12];	char _off_volume4;                        //매도거래량4          
	char bid_volume4[12];	char _bid_volume4;                        //매수거래량4          
	char off_tra5[6];	char _off_tra5;                           //매도거래원5          
	char bid_tra5[6];	char _bid_tra5;                           //매수거래원5          
	char off_volume5[12];	char _off_volume5;                        //매도거래량5          
	char bid_volume5[12];	char _bid_volume5;                        //매수거래량5          
	char off_vol_all[12];	char _off_vol_all;                        //매도외국인거래량     
	char bid_vol_all[12];	char _bid_vol_all;                        //매수외국인거래량     
	char all_off_vol[12];	char _all_off_vol;                        //전체거래원매도합     
	char all_bid_vol[12];	char _all_bid_vol;                        //전체거래원매수합     
} TIVWELWREQ01Out3;

typedef struct tagIVWELWREQ01Out4    //ELW변동거래량자료, [반복]
{
	char bsop_hour[8];	char _bsop_hour;                          //시간                 
	char price[10];	char _price;                              //현재가               
	char sign[1];	char _sign;                               //등락부호             
	char change[10];	char _change;                             //등락폭               
	char offer[10];	char _offer;                              //매도호가             
	char bid[10];	char _bid;                                //매수호가             
	char volume[12];	char _volume;                             //거래량               
	char movvol[12];	char _movvol;                             //변동량               
} TIVWELWREQ01Out4;

typedef struct tagIVWELWREQ01Out5    //KOSPI200기초자산정보
{
	char code6[6];	char _code6;                              //기초자산코드6        
	char hname6[40];	char _hname6;                             //기초자산명6          
	char price6[8];	char _price6;                             //현재가6              
	char sign6[1];	char _sign6;                              //등락부호6            
	char change6[8];	char _change6;                            //등락폭6              
	char chrate6[5];	char _chrate6;                            //등락률6              
	char comrate6[5];	char _comrate6;                           //구성비6              
	char pastv6[5];	char _pastv6;                             //과거변동성6          
} TIVWELWREQ01Out5;

typedef struct tagIVWELWREQ01CntBK    //전송건수블럭
{
	char out1_cnt[6];	char _out1_cnt;                           //Out1Cnt              
	char out2_cnt[6];	char _out2_cnt;                           //Out2Cnt              
	char out3_cnt[6];	char _out3_cnt;                           //Out3Cnt              
	char out4_cnt[6];	char _out4_cnt;                           //Out4Cnt              
	char out5_cnt[6];	char _out5_cnt;                           //Out5Cnt              
} TIVWELWREQ01CntBK;

typedef struct tagIVWELWREQ01
{
	TIVWELWREQ01In                    ivwelwreq01in;  //기본입력 
	TIVWELWREQ01Out1                  ivwelwreq01out1;  //종목마스타기본자료 
	TIVWELWREQ01Out2                  ivwelwreq01out2;  //기초자산정보 
	TIVWELWREQ01Out3                  ivwelwreq01out3;  //거래원정보 
	TIVWELWREQ01Out4                  ivwelwreq01out4[30];  //ELW변동거래량자료 , [반복]
	TIVWELWREQ01Out5                  ivwelwreq01out5;  //KOSPI200기초자산정보 
	TIVWELWREQ01CntBK                 ivwelwreq01cntbk;  //전송건수블럭 
} TIVWELWREQ01;

typedef struct tagIVWVIPREQ01In    //입력Data
{
	char gubun[1];	char _gubun;                              //선옵구분             /*f:KRX선물,o:KRX옵션,w:KP200위클리옵션,u:내부선물,p:내부옵션,z:내부KP200위클리옵션*/
} TIVWVIPREQ01In;

typedef struct tagIVWVIPREQ01Out    //코드출력, [반복]
{
	char code[9];	char _code;                               //code                 
	char namez[40];	char _namez;                              //name                 
} TIVWVIPREQ01Out;

typedef struct tagIVWVIPREQ01
{
	TIVWVIPREQ01In                    ivwvipreq01in;  //입력Data 
	TIVWVIPREQ01Out                   ivwvipreq01out[20];  //코드출력 , [반복]
} TIVWVIPREQ01;

typedef struct tagIVWETPREQ01In    //기본입력
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             
} TIVWETPREQ01In;

typedef struct tagIVWETPREQ01Out1    //종목마스타기본자료
{
	char shrn_iscd[6];	char _shrn_iscd;                          //종목코드             
	char hts_kor_isnm[41];	char _hts_kor_isnm;                       //종목명               
	char stck_prpr[10];	char _stck_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[10];	char _prdy_vrss;                          //등락폭               
	char prdy_ctrt[5];	char _prdy_ctrt;                          //등락률               
	char askp[10];	char _askp;                               //매도호가             
	char bidp[10];	char _bidp;                               //매수호가             
	char acml_vol[12];	char _acml_vol;                           //거래량               
	char acml_rate[6];	char _acml_rate;                          //거래비율             
	char yu_rate[5];	char _yu_rate;                            //유동주회전율         
	char acml_tr_pbmn[12];	char _acml_tr_pbmn;                       //거래대금             
	char stck_mxpr[10];	char _stck_mxpr;                          //상한가               
	char stck_hgpr[10];	char _stck_hgpr;                          //고가                 
	char stck_oprc[10];	char _stck_oprc;                          //시가                 
	char oprc_sign[1];	char _oprc_sign;                          //시가대비부호         
	char oprc_vrss[10];	char _oprc_vrss;                          //시가대비등락폭       
	char stck_lwpr[10];	char _stck_lwpr;                          //저가                 
	char stck_llam[10];	char _stck_llam;                          //하한가               
	char bsop_hour[8];	char _bsop_hour;                          //호가시간             
	char askp1[10];	char _askp1;                              //매도1호가            
	char askp2[10];	char _askp2;                              //매도2호가            
	char askp3[10];	char _askp3;                              //매도3호가            
	char askp4[10];	char _askp4;                              //매도4호가            
	char askp5[10];	char _askp5;                              //매도5호가            
	char askp6[10];	char _askp6;                              //매도6호가            
	char askp7[10];	char _askp7;                              //매도7호가            
	char askp8[10];	char _askp8;                              //매도8호가            
	char askp9[10];	char _askp9;                              //매도9호가            
	char askp10[10];	char _askp10;                             //매도10호가           
	char bidp1[10];	char _bidp1;                              //매수1호가            
	char bidp2[10];	char _bidp2;                              //매수2호가            
	char bidp3[10];	char _bidp3;                              //매수3호가            
	char bidp4[10];	char _bidp4;                              //매수4호가            
	char bidp5[10];	char _bidp5;                              //매수5호가            
	char bidp6[10];	char _bidp6;                              //매수6호가            
	char bidp7[10];	char _bidp7;                              //매수7호가            
	char bidp8[10];	char _bidp8;                              //매수8호가            
	char bidp9[10];	char _bidp9;                              //매수9호가            
	char bidp10[10];	char _bidp10;                             //매수10호가           
	char askp_rsqn1[12];	char _askp_rsqn1;                         //매도1호가잔량        
	char askp_rsqn2[12];	char _askp_rsqn2;                         //매도2호가잔량        
	char askp_rsqn3[12];	char _askp_rsqn3;                         //매도3호가잔량        
	char askp_rsqn4[12];	char _askp_rsqn4;                         //매도4호가잔량        
	char askp_rsqn5[12];	char _askp_rsqn5;                         //매도5호가잔량        
	char askp_rsqn6[12];	char _askp_rsqn6;                         //매도6호가잔량        
	char askp_rsqn7[12];	char _askp_rsqn7;                         //매도7호가잔량        
	char askp_rsqn8[12];	char _askp_rsqn8;                         //매도8호가잔량        
	char askp_rsqn9[12];	char _askp_rsqn9;                         //매도9호가잔량        
	char askp_rsqn10[12];	char _askp_rsqn10;                        //매도10호가잔량       
	char bidp_rsqn1[12];	char _bidp_rsqn1;                         //매수1호가잔량        
	char bidp_rsqn2[12];	char _bidp_rsqn2;                         //매수2호가잔량        
	char bidp_rsqn3[12];	char _bidp_rsqn3;                         //매수3호가잔량        
	char bidp_rsqn4[12];	char _bidp_rsqn4;                         //매수4호가잔량        
	char bidp_rsqn5[12];	char _bidp_rsqn5;                         //매수5호가잔량        
	char bidp_rsqn6[12];	char _bidp_rsqn6;                         //매수6호가잔량        
	char bidp_rsqn7[12];	char _bidp_rsqn7;                         //매수7호가잔량        
	char bidp_rsqn8[12];	char _bidp_rsqn8;                         //매수8호가잔량        
	char bidp_rsqn9[12];	char _bidp_rsqn9;                         //매수9호가잔량        
	char bidp_rsqn10[12];	char _bidp_rsqn10;                        //매수10호가잔량       
	char total_askp_rsqn[12];	char _total_askp_rsqn;                    //총매도호가잔량       
	char total_bidp_rsqn[12];	char _total_bidp_rsqn;                    //총매수호가잔량       
	char ovtm_askp_rsqn[12];	char _ovtm_askp_rsqn;                     //시간외매도잔량       
	char ovtm_bidp_rsqn[12];	char _ovtm_bidp_rsqn;                     //시간외매수잔량       
	char pvt_scnd_dmrs[10];	char _pvt_scnd_dmrs;                      //피벗2차저항          
	char pvt_frst_dmrs[10];	char _pvt_frst_dmrs;                      //피벗1차저항          
	char pvt_pont_val[10];	char _pvt_pont_val;                       //피벗가               
	char pvt_frst_dmsp[10];	char _pvt_frst_dmsp;                      //피벗1차지지          
	char pvt_scnd_dmsp[10];	char _pvt_scnd_dmsp;                      //피벗2차지지          
	char mrkt_div_code[6];	char _mrkt_div_code;                      //코스닥코스피구분     
	char bstp_cls_code[6];	char _bstp_cls_code;                      //지수코드             
	char bstp_kor_isnm[40];	char _bstp_kor_isnm;                      //업종명               
	char cap_size[6];	char _cap_size;                           //자본금규모           
	char stac_month[16];	char _stac_month;                         //결산월               
	char marcket1z16[16];	char _marcket1z16;                        //시장조치1            
	char marcket2z16[16];	char _marcket2z16;                        //시장조치2            
	char marcket3z16[16];	char _marcket3z16;                        //시장조치3            
	char marcket4z16[16];	char _marcket4z16;                        //시장조치4            
	char marcket5z16[16];	char _marcket5z16;                        //시장조치5            
	char marcket6z16[16];	char _marcket6z16;                        //시장조치6            
	char cb_text[6];	char _cb_text;                            //CB구분               
	char stck_fcam[10];	char _stck_fcam;                          //액면가               
	char prdy_clpr_title[12];	char _prdy_clpr_title;                    //전일종가타이틀       
	char prdy_clpr[10];	char _prdy_clpr;                          //전일종가             
	char stck_sspr[10];	char _stck_sspr;                          //대용가               
	char gongpricez7[10];	char _gongpricez7;                        //공모가               
	char d5_hgpr[10];	char _d5_hgpr;                            //5일고가              
	char d5_lwpr[10];	char _d5_lwpr;                            //5일저가              
	char d20_hgpr[10];	char _d20_hgpr;                           //20일고가             
	char d20_lwpr[10];	char _d20_lwpr;                           //20일저가             
	char w52_hgpr[10];	char _w52_hgpr;                           //52주최고가           
	char w52_lwpr[10];	char _w52_lwpr;                           //52주최저가           
	char move_stcn[12];	char _move_stcn;                          //유동주식수           
	char lstn_stcn1[12];	char _lstn_stcn1;                         //상장주식수_천주      
	char hts_avls[12];	char _hts_avls;                           //시가총액             
	char cntg_hour[5];	char _cntg_hour;                          //시간                 
	char seln_mbcr_no1[6];	char _seln_mbcr_no1;                      //매도거래원1          
	char shnu_mbcr_no1[6];	char _shnu_mbcr_no1;                      //매수거래원1          
	char seln_acml_vol1[12];	char _seln_acml_vol1;                     //매도거래량1          
	char shnu_acml_vol1[12];	char _shnu_acml_vol1;                     //매수거래량1          
	char seln_mbcr_no2[6];	char _seln_mbcr_no2;                      //매도거래원2          
	char shnu_mbcr_no2[6];	char _shnu_mbcr_no2;                      //매수거래원2          
	char seln_acml_vol2[12];	char _seln_acml_vol2;                     //매도거래량2          
	char shnu_acml_vol2[12];	char _shnu_acml_vol2;                     //매수거래량2          
	char seln_mbcr_no3[6];	char _seln_mbcr_no3;                      //매도거래원3          
	char shnu_mbcr_no3[6];	char _shnu_mbcr_no3;                      //매수거래원3          
	char seln_acml_vol3[12];	char _seln_acml_vol3;                     //매도거래량3          
	char shnu_acml_vol3[12];	char _shnu_acml_vol3;                     //매수거래량3          
	char seln_mbcr_no4[6];	char _seln_mbcr_no4;                      //매도거래원4          
	char shnu_mbcr_no4[6];	char _shnu_mbcr_no4;                      //매수거래원4          
	char seln_acml_vol4[12];	char _seln_acml_vol4;                     //매도거래량4          
	char shnu_acml_vol4[12];	char _shnu_acml_vol4;                     //매수거래량4          
	char seln_mbcr_no5[6];	char _seln_mbcr_no5;                      //매도거래원5          
	char shnu_mbcr_no5[6];	char _shnu_mbcr_no5;                      //매수거래원5          
	char seln_acml_vol5[12];	char _seln_acml_vol5;                     //매도거래량5          
	char shnu_acml_vol5[12];	char _shnu_acml_vol5;                     //매수거래량5          
	char seln_frgn_vol[12];	char _seln_frgn_vol;                      //매도외국인거래량     
	char shnu_frgn_vol[12];	char _shnu_frgn_vol;                      //매수외국인거래량     
	char frgn_hour[6];	char _frgn_hour;                          //외국인시간           
	char for_rate[5];	char _for_rate;                           //외국인지분율         
	char settdatez4[4];	char _settdatez4;                         //결제일               
	char cratez5[5];	char _cratez5;                            //잔고비율(%)          
	char yudatez4[4];	char _yudatez4;                           //유상기준일           
	char mudatez4[4];	char _mudatez4;                           //무상기준일           
	char yuratez5[5];	char _yuratez5;                           //유상배정비율         
	char muratez5[5];	char _muratez5;                           //무상배정비율         
	char lstn_date[8];	char _lstn_date;                          //상장일               
	char lstn_stcn[12];	char _lstn_stcn;                          //상장주식수_주        
	char total_seln_qty[12];	char _total_seln_qty;                     //전체거래원매도합     
	char total_shnu_qty[12];	char _total_shnu_qty;                     //전체거래원매수합     
	char new_volume[12];	char _new_volume;                         //신규거래량           
} TIVWETPREQ01Out1;

typedef struct tagIVWETPREQ01Out2    //변동거래량자료, [반복]
{
	char bsop_hour[8];	char _bsop_hour;                          //시간                 
	char stck_prpr[10];	char _stck_prpr;                          //현재가               
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[10];	char _prdy_vrss;                          //등락폭               
	char askp[10];	char _askp;                               //매도호가             
	char bidp[10];	char _bidp;                               //매수호가             
	char cntg_vol[12];	char _cntg_vol;                           //변동거래량           
	char acml_vol[12];	char _acml_vol;                           //누적거래량           
} TIVWETPREQ01Out2;

typedef struct tagIVWETPREQ01Out3    //예상체결
{
	char aspr_cls_code[1];	char _aspr_cls_code;                      //동시호가구분         
	char antc_cnpr[10];	char _antc_cnpr;                          //예상체결가           
	char antc_sign[1];	char _antc_sign;                          //예상체결부호         
	char antc_vrss[10];	char _antc_vrss;                          //예상체결등락폭       
	char antc_ctrt[5];	char _antc_ctrt;                          //예상체결등락률       
	char antc_vol[12];	char _antc_vol;                           //예상체결수량         
} TIVWETPREQ01Out3;

typedef struct tagIVWETPREQ01Out4    //ETF자료
{
	char bu12[1];	char _bu12;                               //ETF구분              
	char itmt_last_nav[10];	char _itmt_last_nav;                      //장중/최종NAV         
	char nav_sign[1];	char _nav_sign;                           //NAV등락부호          
	char nav_vrss[10];	char _nav_vrss;                           //NAV등락폭            
	char prdy_last_nav[10];	char _prdy_last_nav;                      //전일NAV              
	char dprt[10];	char _dprt;                               //괴리율               
	char dprt_sign[1];	char _dprt_sign;                          //괴리율부호           
	char cnfg_cnt[10];	char _cnfg_cnt;                           //구성종목수           
	char totvalue[12];	char _totvalue;                           //순자산총액(억원)     
	char trc_errt[10];	char _trc_errt;                           //추적오차율           
	char lp_askp_rsqn1[12];	char _lp_askp_rsqn1;                      //LP매도호가잔량1      
	char lp_askp_rsqn2[12];	char _lp_askp_rsqn2;                      //LP매도호가잔량2      
	char lp_askp_rsqn3[12];	char _lp_askp_rsqn3;                      //LP매도호가잔량3      
	char lp_askp_rsqn4[12];	char _lp_askp_rsqn4;                      //LP매도호가잔량4      
	char lp_askp_rsqn5[12];	char _lp_askp_rsqn5;                      //LP매도호가잔량5      
	char lp_askp_rsqn6[12];	char _lp_askp_rsqn6;                      //LP매도호가잔량6      
	char lp_askp_rsqn7[12];	char _lp_askp_rsqn7;                      //LP매도호가잔량7      
	char lp_askp_rsqn8[12];	char _lp_askp_rsqn8;                      //LP매도호가잔량8      
	char lp_askp_rsqn9[12];	char _lp_askp_rsqn9;                      //LP매도호가잔량9      
	char lp_askp_rsqn10[12];	char _lp_askp_rsqn10;                     //LP매도호가잔량10     
	char lp_bidp_rsqn1[12];	char _lp_bidp_rsqn1;                      //LP매수호가잔량1      
	char lp_bidp_rsqn2[12];	char _lp_bidp_rsqn2;                      //LP매수호가잔량2      
	char lp_bidp_rsqn3[12];	char _lp_bidp_rsqn3;                      //LP매수호가잔량3      
	char lp_bidp_rsqn4[12];	char _lp_bidp_rsqn4;                      //LP매수호가잔량4      
	char lp_bidp_rsqn5[12];	char _lp_bidp_rsqn5;                      //LP매수호가잔량5      
	char lp_bidp_rsqn6[12];	char _lp_bidp_rsqn6;                      //LP매수호가잔량6      
	char lp_bidp_rsqn7[12];	char _lp_bidp_rsqn7;                      //LP매수호가잔량7      
	char lp_bidp_rsqn8[12];	char _lp_bidp_rsqn8;                      //LP매수호가잔량8      
	char lp_bidp_rsqn9[12];	char _lp_bidp_rsqn9;                      //LP매수호가잔량9      
	char lp_bidp_rsqn10[12];	char _lp_bidp_rsqn10;                     //LP매수호가잔량10     
	char clon_cls_code[12];	char _clon_cls_code;                      //ETF복제방법구분코드  
	char txtn_type_code[18];	char _txtn_type_code;                     //ETF과세유형코드      
} TIVWETPREQ01Out4;

typedef struct tagIVWETPREQ01Out5    //ETF기초지수자료
{
	char bstp_cls_code[6];	char _bstp_cls_code;                      //지수코드             
	char bstp_kor_isnm[40];	char _bstp_kor_isnm;                      //지수명               
	char prpr_nmix[10];	char _prpr_nmix;                          //지수                 
	char prdy_vrss_sign[1];	char _prdy_vrss_sign;                     //등락부호             
	char prdy_vrss[10];	char _prdy_vrss;                          //등락폭               
	char ubjiid[6];	char _ubjiid;                             //채권지수코드         
	char ubjiid2[1];	char _ubjiid2;                            //채권지수세부코드     
	char ubjisu[10];	char _ubjisu;                             //채권지수             
	char ubsign[1];	char _ubsign;                             //채권등락부호         
	char ubchange[10];	char _ubchange;                           //채권등락폭           
	char symbol[12];	char _symbol;                             //해외지수심볼         
	char ovrs_nmix[10];	char _ovrs_nmix;                          //해외지수             
	char ovrs_sign[1];	char _ovrs_sign;                          //해외지수등락부호     
	char ovrs_vrss[10];	char _ovrs_vrss;                          //해외지수등락폭       
	char jisukpgubun[1];	char _jisukpgubun;                        //지수거래소구분       /*1:코스피,2:코스닥*/
} TIVWETPREQ01Out5;

typedef struct tagIVWETPREQ01
{
	TIVWETPREQ01In                    ivwetpreq01in;  //기본입력 
	TIVWETPREQ01Out1                  ivwetpreq01out1;  //종목마스타기본자료 
	TIVWETPREQ01Out2                  ivwetpreq01out2[20];  //변동거래량자료 , [반복]
	TIVWETPREQ01Out3                  ivwetpreq01out3;  //예상체결 
	TIVWETPREQ01Out4                  ivwetpreq01out4;  //ETF자료 
	TIVWETPREQ01Out5                  ivwetpreq01out5;  //ETF기초지수자료 
} TIVWETPREQ01;

typedef struct tagIVWVIPREQ02In    //입력Data
{
	char gubun[1];	char _gubun;                              //검색구분             /*1:주식,2:ELW,3:선물,4:옵션,5:주식(코스피),6:주식(코스닥)7미니선물,8미니옵션*/
} TIVWVIPREQ02In;

typedef struct tagIVWVIPREQ02Out    //OutBlockAlias, [반복]
{
	char code[6];	char _code;                               //단축코드             
	char expcode[12];	char _expcode;                            //KRX코드              
	char hnamez40[80];	char _hnamez40;                           //종목명               
	char filler[30];	char _filler;                             //Filler               
} TIVWVIPREQ02Out;

typedef struct tagIVWVIPREQ02
{
	TIVWVIPREQ02In                    ivwvipreq02in;  //입력Data 
	TIVWVIPREQ02Out                   ivwvipreq02out[20];  //OutBlockAlias , [반복]
} TIVWVIPREQ02;

typedef struct tagmaInBlock    //입력
{
	char code[6];   //종목코드             
} TmaInBlock;

typedef struct tagmaOutBlock    //출력
{
	char code[6];   //종목코드             
	char hotime[8];   //시간                 
	char dongsi[1];   //동시구분             
	char jeqprice[7];   //예상체결가           
	char jeqsign[1];   //예상등락부호         
	char jeqchange[6];   //예상등락폭           
	char jeqchrate[5];   //예상등락률           
	char jeqvol[9];   //예상체결수량         
	char offer[7];   //매도호가             
	char bid[7];   //매수호가             
	char offerrem[9];   //매도호가잔량         
	char bidrem[9];   //매수호가잔량         
	char krx_mid_prc[7];   //KRX중간가호가        
	char krx_mid_offerrem[9];   //KRX중간가매도호가잔량 
	char krx_mid_bidrem[9];   //KRX중간가매수호가잔량 
	char nxt_mid_prc[7];   //NXT중간가호가        
	char nxt_mid_offerrem[9];   //NXT중간가매도호가잔량 
	char nxt_mid_bidrem[9];   //NXT중간가매수호가잔량 
	char kospigb[1];   //코스피구분           
} TmaOutBlock;

typedef struct tagma
{
	TmaInBlock                        mainblock;  //입력 
	TmaOutBlock                       maoutblock;  //출력 
} Tma;

typedef struct tagoaInBlock    //입력
{
	char code[6];   //종목코드             
} ToaInBlock;

typedef struct tagoaOutBlock    //출력
{
	char code[6];   //종목코드             
	char hotime[8];   //시간                 
	char dongsi[1];   //동시구분             
	char jeqprice[7];   //예상체결가           
	char jeqsign[1];   //예상등락부호         
	char jeqchange[6];   //예상등락폭           
	char jeqchrate[5];   //예상등락률           
	char jeqvol[9];   //예상체결수량         
	char offer[7];   //매도호가             
	char bid[7];   //매수호가             
	char offerrem[9];   //매도호가잔량         
	char bidrem[9];   //매수호가잔량         
	char mid_prc[7];   //중간가호가           
	char mid_offerrem[9];   //중간가매도호가잔량   
	char mid_bidrem[9];   //중간가매수호가잔량   
	char kospigb[1];   //코스피구분           
} ToaOutBlock;

typedef struct tagoa
{
	ToaInBlock                        oainblock;  //입력 
	ToaOutBlock                       oaoutblock;  //출력 
} Toa;

typedef struct tagnaInBlock    //입력
{
	char code[6];   //종목코드             
} TnaInBlock;

typedef struct tagnaOutBlock    //출력
{
	char code[6];   //종목코드             
	char hotime[8];   //시간                 
	char dongsi[1];   //동시구분             
	char jeqprice[7];   //예상체결가           
	char jeqsign[1];   //예상등락부호         
	char jeqchange[6];   //예상등락폭           
	char jeqchrate[5];   //예상등락률           
	char jeqvol[9];   //예상체결수량         
	char offer[7];   //매도호가             
	char bid[7];   //매수호가             
	char offerrem[9];   //매도호가잔량         
	char bidrem[9];   //매수호가잔량         
	char mid_prc[7];   //중간가호가           
	char mid_offerrem[9];   //중간가매도호가잔량   
	char mid_bidrem[9];   //중간가매수호가잔량   
	char kospigb[1];   //코스피구분           
} TnaOutBlock;

typedef struct tagna
{
	TnaInBlock                        nainblock;  //입력 
	TnaOutBlock                       naoutblock;  //출력 
} Tna;

typedef struct tagmbInBlock    //입력
{
	char code[6];   //종목코드             
} TmbInBlock;

typedef struct tagmbOutBlock    //출력
{
	char code[6];   //종목코드             
	char hotime[8];   //시간                 
	char offer[7];   //매도호가             
	char bid[7];   //매수호가             
	char offerrem[9];   //매도호가잔량         
	char bidrem[9];   //매수호가잔량         
	char P_offer[7];   //차매도호가           
	char P_bid[7];   //차매수호가           
	char P_offerrem[9];   //차매도호가잔량       
	char P_bidrem[9];   //차매수호가잔량       
	char S_offer[7];   //차차매도호가         
	char S_bid[7];   //차차매수호가         
	char S_offerrem[9];   //차차매도호가잔량     
	char S_bidrem[9];   //차차매수호가잔량     
	char S4_offer[7];   //4차매도호가          
	char S4_bid[7];   //4차매수호가          
	char S4_offerrem[9];   //4차매도호가잔량      
	char S4_bidrem[9];   //4차매수호가잔량      
	char S5_offer[7];   //5차매도호가          
	char S5_bid[7];   //5차매수호가          
	char S5_offerrem[9];   //5차매도호가잔량      
	char S5_bidrem[9];   //5차매수호가잔량      
	char T_offerrem[9];   //총매도호가잔량       
	char T_bidrem[9];   //총매수호가잔량       
	char S6_offer[7];   //6차매도호가          
	char S6_bid[7];   //6차매수호가          
	char S6_offerrem[9];   //6차매도호가잔량      
	char S6_bidrem[9];   //6차매수호가잔량      
	char S7_offer[7];   //7차매도호가          
	char S7_bid[7];   //7차매수호가          
	char S7_offerrem[9];   //7차매도호가잔량      
	char S7_bidrem[9];   //7차매수호가잔량      
	char S8_offer[7];   //8차매도호가          
	char S8_bid[7];   //8차매수호가          
	char S8_offerrem[9];   //8차매도호가잔량      
	char S8_bidrem[9];   //8차매수호가잔량      
	char S9_offer[7];   //9차매도호가          
	char S9_bid[7];   //9차매수호가          
	char S9_offerrem[9];   //9차매도호가잔량      
	char S9_bidrem[9];   //9차매수호가잔량      
	char S10_offer[7];   //10차매도호가         
	char S10_bid[7];   //10차매수호가         
	char S10_offerrem[9];   //10차매도호가잔량     
	char S10_bidrem[9];   //10차매수호가잔량     
	char volume[9];   //누적거래량           
	char krx_mid_prc[7];   //KRX중간가호가        
	char krx_mid_offerrem[9];   //KRX중간가매도호가잔량 
	char krx_mid_bidrem[9];   //KRX중간가매수호가잔량 
	char nxt_mid_prc[7];   //NXT중간가호가        
	char nxt_mid_offerrem[9];   //NXT중간가매도호가잔량 
	char nxt_mid_bidrem[9];   //NXT중간가매수호가잔량 
	char kospigb[1];   //코스피구분           
} TmbOutBlock;

typedef struct tagmb
{
	TmbInBlock                        mbinblock;  //입력 
	TmbOutBlock                       mboutblock;  //출력 
} Tmb;

typedef struct tagobInBlock    //입력
{
	char code[6];   //종목코드             
} TobInBlock;

typedef struct tagobOutBlock    //출력
{
	char code[6];   //종목코드             
	char hotime[8];   //시간                 
	char offer[7];   //매도호가             
	char bid[7];   //매수호가             
	char offerrem[9];   //매도호가잔량         
	char bidrem[9];   //매수호가잔량         
	char P_offer[7];   //차매도호가           
	char P_bid[7];   //차매수호가           
	char P_offerrem[9];   //차매도호가잔량       
	char P_bidrem[9];   //차매수호가잔량       
	char S_offer[7];   //차차매도호가         
	char S_bid[7];   //차차매수호가         
	char S_offerrem[9];   //차차매도호가잔량     
	char S_bidrem[9];   //차차매수호가잔량     
	char S4_offer[7];   //4차매도호가          
	char S4_bid[7];   //4차매수호가          
	char S4_offerrem[9];   //4차매도호가잔량      
	char S4_bidrem[9];   //4차매수호가잔량      
	char S5_offer[7];   //5차매도호가          
	char S5_bid[7];   //5차매수호가          
	char S5_offerrem[9];   //5차매도호가잔량      
	char S5_bidrem[9];   //5차매수호가잔량      
	char T_offerrem[9];   //총매도호가잔량       
	char T_bidrem[9];   //총매수호가잔량       
	char S6_offer[7];   //6차매도호가          
	char S6_bid[7];   //6차매수호가          
	char S6_offerrem[9];   //6차매도호가잔량      
	char S6_bidrem[9];   //6차매수호가잔량      
	char S7_offer[7];   //7차매도호가          
	char S7_bid[7];   //7차매수호가          
	char S7_offerrem[9];   //7차매도호가잔량      
	char S7_bidrem[9];   //7차매수호가잔량      
	char S8_offer[7];   //8차매도호가          
	char S8_bid[7];   //8차매수호가          
	char S8_offerrem[9];   //8차매도호가잔량      
	char S8_bidrem[9];   //8차매수호가잔량      
	char S9_offer[7];   //9차매도호가          
	char S9_bid[7];   //9차매수호가          
	char S9_offerrem[9];   //9차매도호가잔량      
	char S9_bidrem[9];   //9차매수호가잔량      
	char S10_offer[7];   //10차매도호가         
	char S10_bid[7];   //10차매수호가         
	char S10_offerrem[9];   //10차매도호가잔량     
	char S10_bidrem[9];   //10차매수호가잔량     
	char volume[9];   //누적거래량           
	char mid_prc[7];   //중간가호가           
	char mid_offerrem[9];   //중간가매도호가잔량   
	char mid_bidrem[9];   //중간가매수호가잔량   
	char kospigb[1];   //코스피구분           
} TobOutBlock;

typedef struct tagob
{
	TobInBlock                        obinblock;  //입력 
	TobOutBlock                       oboutblock;  //출력 
} Tob;

typedef struct tagnbInBlock    //입력
{
	char code[6];   //종목코드             
} TnbInBlock;

typedef struct tagnbOutBlock    //출력
{
	char code[6];   //종목코드             
	char hotime[8];   //시간                 
	char offer[7];   //매도호가             
	char bid[7];   //매수호가             
	char offerrem[9];   //매도호가잔량         
	char bidrem[9];   //매수호가잔량         
	char P_offer[7];   //차매도호가           
	char P_bid[7];   //차매수호가           
	char P_offerrem[9];   //차매도호가잔량       
	char P_bidrem[9];   //차매수호가잔량       
	char S_offer[7];   //차차매도호가         
	char S_bid[7];   //차차매수호가         
	char S_offerrem[9];   //차차매도호가잔량     
	char S_bidrem[9];   //차차매수호가잔량     
	char S4_offer[7];   //4차매도호가          
	char S4_bid[7];   //4차매수호가          
	char S4_offerrem[9];   //4차매도호가잔량      
	char S4_bidrem[9];   //4차매수호가잔량      
	char S5_offer[7];   //5차매도호가          
	char S5_bid[7];   //5차매수호가          
	char S5_offerrem[9];   //5차매도호가잔량      
	char S5_bidrem[9];   //5차매수호가잔량      
	char T_offerrem[9];   //총매도호가잔량       
	char T_bidrem[9];   //총매수호가잔량       
	char S6_offer[7];   //6차매도호가          
	char S6_bid[7];   //6차매수호가          
	char S6_offerrem[9];   //6차매도호가잔량      
	char S6_bidrem[9];   //6차매수호가잔량      
	char S7_offer[7];   //7차매도호가          
	char S7_bid[7];   //7차매수호가          
	char S7_offerrem[9];   //7차매도호가잔량      
	char S7_bidrem[9];   //7차매수호가잔량      
	char S8_offer[7];   //8차매도호가          
	char S8_bid[7];   //8차매수호가          
	char S8_offerrem[9];   //8차매도호가잔량      
	char S8_bidrem[9];   //8차매수호가잔량      
	char S9_offer[7];   //9차매도호가          
	char S9_bid[7];   //9차매수호가          
	char S9_offerrem[9];   //9차매도호가잔량      
	char S9_bidrem[9];   //9차매수호가잔량      
	char S10_offer[7];   //10차매도호가         
	char S10_bid[7];   //10차매수호가         
	char S10_offerrem[9];   //10차매도호가잔량     
	char S10_bidrem[9];   //10차매수호가잔량     
	char volume[9];   //누적거래량           
	char mid_prc[7];   //중간가호가           
	char mid_offerrem[9];   //중간가매도호가잔량   
	char mid_bidrem[9];   //중간가매수호가잔량   
	char kospigb[1];   //코스피구분           
} TnbOutBlock;

typedef struct tagnb
{
	TnbInBlock                        nbinblock;  //입력 
	TnbOutBlock                       nboutblock;  //출력 
} Tnb;

typedef struct tagmcInBlock    //입력
{
	char code[6];	char _code;                               //종목코드             
} TmcInBlock;

typedef struct tagmcOutBlock    //출력
{
	char code[6];	char _code;                               //종목코드             
	char time[8];	char _time;                               //시간                 
	char sign[1];	char _sign;                               //등락부호             
	char change[6];	char _change;                             //등락폭               
	char price[7];	char _price;                              //현재가               
	char chrate[5];	char _chrate;                             //등락률               
	char high[7];	char _high;                               //고가                 
	char low[7];	char _low;                                //저가                 
	char offer[7];	char _offer;                              //매도호가             
	char bid[7];	char _bid;                                //매수호가             
	char volume[9];	char _volume;                             //거래량               
	char volrate[6];	char _volrate;                            //거래량전일비         
	char movolume[8];	char _movolume;                           //변동거래량           
	char value[9];	char _value;                              //거래대금             
	char open[7];	char _open;                               //시가                 
	char avgprice[7];	char _avgprice;                           //가중평균가           
	char janggubun[1];	char _janggubun;                          //장구분               
	char bidrate[6];	char _bidrate;                            //매수비중             
	char volpower[6];	char _volpower;                           //체결강도             
	char new_volume[12];	char _new_volume;                         //누적거래량           
	char bidvolall[12];	char _bidvolall;                          //누적매수체결량       
	char offvolall[12];	char _offvolall;                          //누적매도체결량       
	char kospigb[1];	char _kospigb;                            //코스피구분           
	char value_won[15];	char _value_won;                          //거래대금원           
} TmcOutBlock;

typedef struct tagmc
{
	TmcInBlock                        mcinblock;  //입력 
	TmcOutBlock                       mcoutblock;  //출력 
} Tmc;

typedef struct tagInBlock    //입력
{
	char code[6];	char _code;                               //종목코드             
} TInBlock;

typedef struct tagOutBlock    //출력
{
	char code[6];	char _code;                               //종목코드             
	char time[8];	char _time;                               //시간                 
	char sign[1];	char _sign;                               //등락부호             
	char change[6];	char _change;                             //등락폭               
	char price[7];	char _price;                              //현재가               
	char chrate[5];	char _chrate;                             //등락률               
	char high[7];	char _high;                               //고가                 
	char low[7];	char _low;                                //저가                 
	char offer[7];	char _offer;                              //매도호가             
	char bid[7];	char _bid;                                //매수호가             
	char volume[9];	char _volume;                             //거래량               
	char volrate[6];	char _volrate;                            //거래량전일비         
	char movolume[8];	char _movolume;                           //변동거래량           
	char value[9];	char _value;                              //거래대금             
	char open[7];	char _open;                               //시가                 
	char avgprice[7];	char _avgprice;                           //가중평균가           
	char janggubun[1];	char _janggubun;                          //장구분               
	char bidrate[6];	char _bidrate;                            //매수비중             
	char volpower[6];	char _volpower;                           //체결강도             
	char new_volume[12];	char _new_volume;                         //누적거래량           
	char bidvolall[12];	char _bidvolall;                          //누적매수체결량       
	char offvolall[12];	char _offvolall;                          //누적매도체결량       
	char kospigb[1];	char _kospigb;                            //코스피구분           
	char value_won[15];	char _value_won;                          //거래대금원                
} TOutBlock;

typedef struct tagoc
{
	TInBlock                          inblock;  //입력 
	TOutBlock                         outblock;  //출력 
} Toc;

typedef struct tagncInBlock    //입력
{
	char code[6];	char _code;                               //종목코드             
} TncInBlock;

typedef struct tagncOutBlock    //출력
{
	char code[6];	char _code;                               //종목코드             
	char time[8];	char _time;                               //시간                 
	char sign[1];	char _sign;                               //등락부호             
	char change[6];	char _change;                             //등락폭               
	char price[7];	char _price;                              //현재가               
	char chrate[5];	char _chrate;                             //등락률               
	char high[7];	char _high;                               //고가                 
	char low[7];	char _low;                                //저가                 
	char offer[7];	char _offer;                              //매도호가             
	char bid[7];	char _bid;                                //매수호가             
	char volume[9];	char _volume;                             //거래량               
	char volrate[6];	char _volrate;                            //거래량전일비         
	char movolume[8];	char _movolume;                           //변동거래량           
	char value[9];	char _value;                              //거래대금             
	char open[7];	char _open;                               //시가                 
	char avgprice[7];	char _avgprice;                           //가중평균가           
	char janggubun[1];	char _janggubun;                          //장구분               
	char bidrate[6];	char _bidrate;                            //매수비중             
	char volpower[6];	char _volpower;                           //체결강도             
	char new_volume[12];	char _new_volume;                         //누적거래량           
	char bidvolall[12];	char _bidvolall;                          //누적매수체결량       
	char offvolall[12];	char _offvolall;                          //누적매도체결량       
	char kospigb[1];	char _kospigb;                            //코스피구분           
	char value_won[15];	char _value_won;                          //거래대금원           
} TncOutBlock;

typedef struct tagnc
{
	TncInBlock                        ncinblock;  //입력 
	TncOutBlock                       ncoutblock;  //출력 
} Tnc;

typedef struct tagfEInBlock    //입력
{
	char fuitem                           [  8];   //종목코드             
} TfEInBlock;

typedef struct tagfEOutBlock    //출력
{
	char fuitem                           [  8];   //종목코드             
	char time                             [  8];   //시간                 
	char dongsi                           [  1];   //동시호가구분         
	char eqsign                           [  1];   //예상등락부호         
	char eqprice                          [  9];   //예상체결가           
	char eqchange                         [  9];   //예상등락폭           
	char eqchrate                         [  5];   //예상등락률           
	char eqvolume                         [  9];   //예상체결수량                //파생시장제도개선(2024.03.13)
} TfEOutBlock;

typedef struct tagfE
{
	TfEInBlock                        feinblock                             ;  //입력 
	TfEOutBlock                       feoutblock                            ;  //출력 
} TfE;

typedef struct tagoEInBlock    //입력
{
	char opitem                           [  8];   //종목코드             
} ToEInBlock;

typedef struct tagoEOutBlock    //출력
{
	char opitem                           [  8];   //종목코드             
	char time                             [  8];   //시간                 
	char dongsi                           [  1];   //동시호가구분         
	char eqsign                           [  1];   //예상등락부호         
	char eqprice                          [  9];   //예상체결가           
	char eqchange                         [  9];   //예상등락폭           
	char eqchrate                         [  5];   //예상등락률           
	char eqvolume                         [  9];   //예상체결수량                //파생시장제도개선(2024.03.13)
} ToEOutBlock;

typedef struct tagoE
{
	ToEInBlock                        oeinblock                             ;  //입력 
	ToEOutBlock                       oeoutblock                            ;  //출력 
} ToE;

typedef struct tagf7InBlock    //입력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
} Tf7InBlock;

typedef struct tagf7OutBlock    //출력
{
	char fuitem                           [  8];	char _fuitem;                             //종목코드             
	char futime                           [  8];	char _futime;                             //시간                 
	char exlmtstep                        [  1];	char _exlmtstep;                          //가격확대예정단계     
	char exlmtgb                          [  1];	char _exlmtgb;                            //가격확대예정 구분    
	char uplmtgb                          [  1];	char _uplmtgb;                            //가격제한확대상한단계 
	char dnlmtgb                          [  1];	char _dnlmtgb;                            //가격제한확대하한단계 
	char uplmtprice                       [  9];	char _uplmtprice;                         //적용된 단계 상한가   
	char dnlmtprice                       [  9];	char _dnlmtprice;                         //적용된 단계 하한가   
} Tf7OutBlock;

typedef struct tagf7
{
	Tf7InBlock                        f7inblock                             ;  //입력 
	Tf7OutBlock                       f7outblock                            ;  //출력 
} Tf7;

typedef struct tago7InBlock    //입력
{
	char opitem                           [  8];	char _opitem;                             //종목코드             
} To7InBlock;

typedef struct tago7OutBlock    //출력
{
	char opitem                           [  8];	char _opitem;                             //종목코드             
	char optime                           [  8];	char _optime;                             //시간                 
	char uplmtgb                          [  1];	char _uplmtgb;                            //가격제한확대상한단계 
	char dnlmtgb                          [  1];	char _dnlmtgb;                            //가격제한확대하한단계 
	char uplmtprice                       [  9];	char _uplmtprice;                         //적용된 단계 상한가   
	char dnlmtprice                       [  9];	char _dnlmtprice;                         //적용된 단계 하한가   
} To7OutBlock;

typedef struct tago7
{
	To7InBlock                        o7inblock                             ;  //입력 
	To7OutBlock                       o7outblock                            ;  //출력 
} To7;
