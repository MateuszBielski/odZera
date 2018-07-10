#include <Moduly.h>

Moduly::Moduly()
{
}

Moduly::~Moduly()
{
}

bool Moduly::DolaczDo(spOkno1 okno)
{
    if(okno == nullptr)return false;
    oknoGlowne = okno;
    return true;
}
int Moduly::Uruchom()
{
    oknoGL = std::make_unique<OknoGL>();
    oknoGL->UstawIzainstalujPrzyciskW(oknoGlowne->refVBox());
    sterowanie = std::make_unique<SterowanieMysza>();
    sterowanie->PodlaczanieSygnalow(*oknoGL);
//    sterowanie->PodlaczanieSygnalow(*(oknoGL->pEkranGL)); - w tej wersji powoduje naruszenie ochrony pamięci
    /*Wykonać  tablicę wskaźników do funkcji u uruchomic je w pętli
     * */
	renderowanie = std::make_shared<Renderowanie>();
	//renderowanie->PodlaczSygnalZ(*(oknoGL->WskEkranGL()));
    
    auto server = std::make_shared<Server>();//odpowiednio jak ekrangl
    auto client = std::make_shared<Client>();//odpowiednio jak render
    
    //server->signal_something().connect(sigc::mem_fun(*client,&Client::on_server_something) );
    client->PodlaczSygnServ(*server);
    server->signal_something().connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));
    oknoGL->RefEkranGL().signal_something().connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));
    std::cout << "Before Server::do_something()" << std::endl;
    server->do_something(); 
    std::cout << "After Server::do_something()" << std::endl;
    std::cout << "Before EkranGL::do_something()" << std::endl;
    oknoGL->RefEkranGL().do_something();
	std::cout << "After EkranGL::do_something()" << std::endl;
	 
}
