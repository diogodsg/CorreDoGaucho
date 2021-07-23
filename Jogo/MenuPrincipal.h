#pragma once
#include "VelhoOeste.h"
#include "Pontuacao.h"
#include "MenuEscolhaFases.h"

// enumera botoes
enum BotoesMenuPrincipal {
    novo_jogo = 0,
    escolha_de_fases,
    lista_de_pontuacoes,
    sair
};

/* Classe do Menu Principal */
class MenuPrincipal :
    public Ente
{
private:
    // armazena os botoes do menu principal
    std::map<int, gui::Botao* > botoes;
    sf::RectangleShape caixaBotoes;
    int botaoAtivo;

public:
    // Construtoras e Destrutoras
    MenuPrincipal(JogoInfo* pji = NULL);
    ~MenuPrincipal();
    
    // Metodos de Inicialização
    void iniciarBotoes();

    // Métodos de Atualização
    void atualizar();
    void atualizarEventos(sf::Event& evento_sfml);
    void trocarBotao(int direcao);
    void GerenciarCliqueBotao();

    // Métodos de Renderização
    void desenhar(sf::RenderTarget& janela);
};

