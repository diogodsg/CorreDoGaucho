#include "stdafx.h"
#include "GerenciadorJogoSalvo.h"

GerenciadorJogoSalvo::GerenciadorJogoSalvo()
{
}

GerenciadorJogoSalvo::~GerenciadorJogoSalvo()
{
}

void GerenciadorJogoSalvo::salvarEstadoDaFase(std::string nome_fase, int qtd_jogadores){
	std::ofstream arquivo_jogo_salvo;
	arquivo_jogo_salvo.open("./Recursos/dados/fase_salva.txt", std::ios::out | std::ios::trunc);
	arquivo_jogo_salvo << nome_fase << " " << qtd_jogadores;
	arquivo_jogo_salvo.close();
}

void GerenciadorJogoSalvo::salvarJogadores(ListaJogadores* lp, int score)
{
	std::ofstream arquivo_jogo_salvo;
	arquivo_jogo_salvo.open("./Recursos/dados/jogadores_salvos.txt", std::ios::out | std::ios::trunc);

	// NOME - POSICAOX - POSICAOY - VIDA - SCORE

	Lista<Jogador>::Elemento<Jogador>* elJogador = lp->getPrimeiro();
	while (elJogador != NULL) {
		Jogador* pJogador = elJogador->getInfo();

		arquivo_jogo_salvo << pJogador->getNome() << " " << pJogador->getPosition().x  << " " << 
			pJogador->getPosition().y << " " << pJogador->getPersInfo()->getHp() << " " << score << "\n";

		elJogador = elJogador->getProximo();
	}
	arquivo_jogo_salvo.close();
}

void GerenciadorJogoSalvo::salvarInimigos(ListaInimigos* li)
{
	std::ofstream arquivo_jogo_salvo;
	arquivo_jogo_salvo.open("./Recursos/dados/inimigos_salvos.txt", std::ios::out | std::ios::trunc);

	// NOME - POSICAOX - POSICAOY - VIDA

	Lista<Inimigo>::Elemento<Inimigo>* elInimigo = li->getPrimeiro();
	while (elInimigo != NULL) {
		Inimigo* pInimigo = elInimigo->getInfo();

		arquivo_jogo_salvo << pInimigo->getNome() << " " << pInimigo->getPosition().x << " " <<
			pInimigo->getPosition().y << " " << pInimigo->getPersInfo()->getHp() << "\n";

		elInimigo = elInimigo->getProximo();
	}
	arquivo_jogo_salvo.close();
}

void GerenciadorJogoSalvo::salvarProjeteis(ListaProjeteis* lp)
{
	std::ofstream arquivo_jogo_salvo;
	arquivo_jogo_salvo.open("./Recursos/dados/projeteis_salvos.txt", std::ios::out | std::ios::trunc);

	// NOME - POSICAOX - POSICAOY - DIRECAO

	Lista<Projetil>::Elemento<Projetil>* elProjetil = lp->getPrimeiro();
	while (elProjetil != NULL) {
		Projetil* pProjetil = elProjetil->getInfo();

		arquivo_jogo_salvo << pProjetil->getNome() << " " << pProjetil->getPosicao().x << " " <<
			pProjetil->getPosicao().y << " " << pProjetil->getDirecao() << "\n";

		elProjetil = elProjetil->getProximo();
	}
	arquivo_jogo_salvo.close();
}

void GerenciadorJogoSalvo::carregarJogadores(ListaJogadores* lj, ListaEntidades* le, ListaProjeteis* lp)
{
	std::string nome;
	sf::Vector2f posicao;
	int score, vida;
	Jogador* jogador = NULL;

	// le arquivo
	std::fstream arquivo_jogo_salvo;
	try {
		arquivo_jogo_salvo.open("./Recursos/dados/jogadores_salvos.txt", std::ios::in);
	}
	catch (...) {
		std::cerr << "MENUPRINCIPAL::CARREGARJOGO FALHA AO CARREGAR JOGO." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// le arquivo

	while (arquivo_jogo_salvo >> nome &&
		arquivo_jogo_salvo >> posicao.x &&
		arquivo_jogo_salvo >> posicao.y &&
		arquivo_jogo_salvo >> vida &&
		arquivo_jogo_salvo >> score) 
	{
		if (nome == "COWBOY") 
			jogador = static_cast<Jogador* >(new Cowboy(lp, le));

		else if (nome == "COWGIRL")
			jogador = static_cast<Jogador*>(new CowGirl(lp, le));

		jogador->setPosicao(posicao.x, posicao.y);
		jogador->setHp(vida);
		PersonagemInfo::setScore(score);
		le->incluirEntidade(static_cast<Entidade* >(jogador));
		lj->incluirJogador(jogador);
	}
	arquivo_jogo_salvo.close();
}

void GerenciadorJogoSalvo::carregarInimigos(ListaInimigos* li, ListaEntidades* le, GeradorProjeteis* gp, ListaJogadores* lj)
{
	std::string nome;
	sf::Vector2f posicao;
	int vida;
	Inimigo* inimigo= NULL;

	// le arquivo
	std::fstream arquivo_jogo_salvo;
	try {
		arquivo_jogo_salvo.open("./Recursos/dados/inimigos_salvos.txt", std::ios::in);
	}
	catch (...) {
		std::cerr << "MENUPRINCIPAL::CARREGARJOGO FALHA AO CARREGAR JOGO." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// le arquivo

	while (arquivo_jogo_salvo >> nome &&
		arquivo_jogo_salvo >> posicao.x &&
		arquivo_jogo_salvo >> posicao.y &&
		arquivo_jogo_salvo >> vida)
	{
		if (nome == "BRUXA")
			inimigo = static_cast<Inimigo*>(new Bruxa(posicao, gp, rand() % 1000 + 1500));

		else if (nome == "COBRA")
			inimigo = static_cast<Inimigo*>(new Cobra(lj, posicao));

		else if (nome == "DRAGAO")
			inimigo = static_cast<Inimigo*>(new Dragao(posicao, gp));

		inimigo->setHp(vida);
		inimigo->setPosicao(posicao.x, posicao.y);
		le->incluirEntidade(static_cast<Entidade*>(inimigo));
		li->incluirInimigo(inimigo);
	}
	arquivo_jogo_salvo.close();
}

void GerenciadorJogoSalvo::carregarProjeteis(ListaProjeteis* lp, ListaEntidades* le)
{
	std::string nome;
	sf::Vector2f posicao;
	int direcao;
	Projetil* projetil = NULL;

	// le arquivo
	std::fstream arquivo_jogo_salvo;
	try {
		arquivo_jogo_salvo.open("./Recursos/dados/projeteis_salvos.txt", std::ios::in);
	}
	catch (...) {
		std::cerr << "MENUPRINCIPAL::CARREGARJOGO FALHA AO CARREGAR JOGO." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// le arquivo

	while (arquivo_jogo_salvo >> nome &&
		arquivo_jogo_salvo >> posicao.x &&
		arquivo_jogo_salvo >> posicao.y &&
		arquivo_jogo_salvo >> direcao)
	{
		if (nome == "MORCEGO")
			projetil = static_cast<Projetil*>(new Morcego(posicao, direcao));

		else if (nome == "COBRA")
			projetil = static_cast<Projetil*>(new Shuriken(posicao, direcao));

		else if (nome == "BOLA_DE_FOGO")
			projetil = static_cast<Projetil*>(new BolaFogo(posicao, direcao));

		le->incluirEntidade(static_cast<Entidade*>(projetil));
		lp->incluirProjetil(projetil);
	}
	arquivo_jogo_salvo.close();
}
