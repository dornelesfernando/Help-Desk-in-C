#include "update_call.h"

int update_call(CallService *call_list, CallHeap *call_list_heap, CallFIFO *call_list_fifo, CallService *call_history, CallService *call_suspend, Arv *arv_tec, int selected_id, int login_control, int cancel_control, char **logs) {
	char log_msg[128];

	CallNode *current_node = call_list->head;
	Call *call_data = NULL;

	while (current_node != NULL) {
		if (current_node->data->id == selected_id) {
			call_data = current_node->data;
			break;
		}

		current_node = current_node->next;
	}
	
	if (call_data == NULL && call_suspend != NULL && call_suspend != call_list) {
        current_node = call_suspend->head;
        while (current_node != NULL) {
            if (current_node->data->id == selected_id) {
                call_data = current_node->data;
                break;
            }
            current_node = current_node->next;
        }
	}

    if (call_data == NULL && arv_tec != NULL && arv_tec->raiz != NULL) {
        buscar_chamado_na_arvore_tecnicos(arv_tec->raiz, selected_id, &call_data);
    }

	if (call_data == NULL) {
		printf(RED BOLD "Erro: chamado com ID %d nC#o encontrado.\n" RESET, selected_id);
		snprintf(log_msg, sizeof(log_msg), "Tentativa de atualizar ID %d falhou (nao encontrado).", selected_id);
		adicionar_log_dinamico(logs, log_msg);
		return 9999;
	}
	snprintf(log_msg, sizeof(log_msg), "Chamado ID %d localizado.", selected_id);
	adicionar_log_dinamico(logs, log_msg);

	while (1) {
		int search_control = 0;

		if (cancel_control) {
			call_data->status = CANCELADO;
			call_data->data_fechamento = time(NULL);
			adicionar_log_dinamico(logs, "Chamado cancelado.");

			// Adiciona na call_history
			Call *newCall = (Call*) malloc(sizeof(Call));

			memcpy(newCall, call_data, sizeof(Call));

			insert_at_end_service(call_history, newCall, logs);
			adicionar_log_dinamico(logs, "Chamado adicionado C  lista history.");
		} else {
			if ((call_data->status == CANCELADO || call_data->status == RESOLVIDO) && !login_control ) return 9997;

			int index = 0;
			int index_control = 0;
			int scanf_control = 0;
			int status = 0;
			int priority_control = 0;
			int priority = 0;
			int email_control = 0;
			char email[100];
			char log_message[128];
			int item = 0;
            int qtd_item = 0;
            char resposta_sn;

			// Buffer para formatar as datas
			char data_str[100];
			struct tm *tm_info;

			snprintf(log_message, sizeof(log_message), "Listando chamado ID: %d.", call_data->id);
			adicionar_log_dinamico(logs, log_message);

			if (call_data == NULL) {
				printf(RED BOLD "Erro: chamado nC#o encontrado (NULL).\n" RESET);
				adicionar_log_dinamico(logs, "Erro: chamado nC#o encontrado (NULL).");
				return 9999;
			}

			header();
			printf("  DETALHES DO CHAMADO ID: " YELLOW "%d" RESET "\n", call_data->id);
			line();

			printf(YELLOW " [%d] " CYAN "Título:     " RESET BOLD "%s\n" RESET, ++index, call_data->title);

			if (login_control) {
				printf(YELLOW " [%d] " CYAN "Status:     " RESET "%s\n", ++index, get_status_styled(call_data->status));
			}

			printf(YELLOW " [%d] " CYAN "Prioridade: " RESET "%s\n", ++index, get_priority_styled(call_data->priority));

			if (login_control) {
				if (strcmp(call_data->name_func, "") == 0) {
					printf(YELLOW " [%d] " CYAN "Atribuído a: " RESET "Nenhum técnico atribuído\n", ++index);
				} else {
					printf(YELLOW " [%d] " CYAN "Atribuído a: " RESET "%s\n", ++index, call_data->name_func);
				}
			}

			printf(MAGENTA "\n--- Solicitante -------------------------------------------\n" RESET);
			printf(YELLOW " [%d] " CYAN "Nome:       " RESET "%s\n", ++index, call_data->name);
			printf(YELLOW " [%d] " CYAN "Email:      " RESET "%s\n", ++index, call_data->email);
			
            printf(MAGENTA "\n--- Itens -------------------------------------------\n" RESET);
            printf(YELLOW " [%d] " CYAN " Item:       " RESET "%s\n", ++index, get_item_char(call_data->item));
            printf(YELLOW " [%d] " CYAN " Quantidade  " RESET "%d\n", ++index, call_data->qtd_item);

			printf(MAGENTA "\n--- Histórico ---------------------------------------------\n" RESET);

			tm_info = localtime(&call_data->created_at);
			strftime(data_str, sizeof(data_str), "%d/%m/%Y C s %H:%M:%S", tm_info);
			printf(CYAN " Criado em:  " RESET "%s\n", data_str);

			if (call_data->updated_at > 0) {
				tm_info = localtime(&call_data->updated_at);
				strftime(data_str, sizeof(data_str), "%d/%m/%Y C s %H:%M:%S", tm_info);
				printf(CYAN " Atualizado: " RESET "%s\n", data_str);
			}

			if (call_data->data_fechamento > 0) {
				tm_info = localtime(&call_data->data_fechamento);
				strftime(data_str, sizeof(data_str), "%d/%m/%Y C s %H:%M:%S", tm_info);
				printf(CYAN " Fechado em: " RESET BOLD "%s\n", data_str);
			}

			printf(MAGENTA "\n--- Descrição do Problema ---------------------------------\n" RESET);
			printf(YELLOW " [%d] " RESET "%s\n", ++index, call_data->desc);

			if (login_control) {
				if (strcmp(call_data->solution, "") != 0) {
					printf(GREEN "\n--- Solução Aplicada --------------------------------------\n" RESET);
					printf(YELLOW " [%d] " GREEN "%s\n" RESET, ++index, call_data->solution);
				}
			}

			line();
			printf(RED " [99] " YELLOW "Retornar ao menu\n" RESET);
			line();

			do {
				printf(YELLOW "\n  --> Digite o índex da informação que deseja alterar: " RESET);
				scanf_control = scanf("%d", &index_control);
				clean_buffer_stdin();

				if (scanf_control) if (index_control == 99) return call_data->id;

				if (scanf_control == 1 && index_control > 0 && index_control <= index) {
					if(login_control) {
						switch (index_control) {
						case 1:
							printf(CYAN  " [1] " RED "--> " RESET);
							scanf(" %149[^\n]", call_data->title);
							clean_buffer_stdin();
							break;
						case 2:
							printf(CYAN   "     0) " YELLOW "Aberto" RESET);
							printf(CYAN   "     1) " BLUE "Em Andamento" RESET);
							printf(CYAN   "     2) " GREEN "Resolvido" RESET);
							printf(CYAN   "     3) " BOLD "Cancelado" RESET);
							printf(CYAN   "     4) " BOLD "Suspenso" RESET);

							do {
								printf(CYAN  "\n [2] " RED "--> " RESET);
								scanf_control = scanf("%d", &status);

								//Verifica status
								if (scanf_control == 1 && status >= 0 && status <= 3) {
									switch (status) {
									case 0:
										call_data->status = ABERTO;
										break;
									case 1:
										call_data->status = EM_ANDAMENTO;
										break;
									case 2:
										call_data->status = RESOLVIDO;
										break;
									case 3:
										call_data->status = CANCELADO;
										break;
									case 4:
										call_data->status = SUSPENSO;
								// 		aqui tem que adicionar na fila de suspensão e remover das filas normais
										break;
									default:
										call_data->status = ABERTO;
										break;
									}
								} else {
									printf(RED  " --> Status invC!lido\n" RESET);
								}

								clean_buffer_stdin();
							} while (!(scanf_control == 1 && status >= 0 && status <= 4));
							adicionar_log_dinamico(logs, "Status validado!");
							break;
						case 3:
							printf(CYAN   "     0) " BLUE "Baixa" RESET);
							printf(CYAN   "     1) " YELLOW "MC)dia" RESET);
							printf(CYAN   "     2) " RED "Alta" RESET);
							printf(CYAN   "     3) " BOLD RED "Urgente" RESET);

							do {
								printf(CYAN  "\n [3] " RED "--> " RESET);
								scanf_control = scanf("%d", &priority);

								//Verifica priority
								if (scanf_control == 1 && priority >= 0 && priority <= 3) {
									switch (priority) {
									case 0:
										call_data->priority = BAIXA;
										break;
									case 1:
										call_data->priority = MEDIA;
										break;
									case 2:
										call_data->priority = ALTA;
										break;
									case 3:
										call_data->priority = URGENTE;
										break;
									default:
										call_data->priority = BAIXA;
										break;
									}
									priority_control = 1;
								} else {
									printf(RED  " --> priority invC!lido\n" RESET);
								}

								clean_buffer_stdin();
							} while (!(scanf_control && priority_control));
							adicionar_log_dinamico(logs, "priority validado!");
							break;
						case 4:
							printf(CYAN  " [4] " RED "--> " RESET);
							scanf(" %99[^\n]", call_data->name_func);
							clean_buffer_stdin();
							break;
						case 5:
							printf(CYAN  " [5] " RED "--> " RESET);
							scanf(" %99[^\n]", call_data->name);
							clean_buffer_stdin();
							break;
						case 6:
							do {
								printf(CYAN  " [6] " RED "--> " RESET);
								scanf(" %99[^\n]", email);
								clean_buffer_stdin();

								char* arroba = strchr(email, '@');
								char* dot = strchr(email, '.');

								//Verifica email
								if (!(arroba == NULL || dot == NULL)) {
									strcpy(call_data->email, email);
									email_control = 1;
								} else {
									printf(RED  " --> Email invC!lido\n" RESET);
								}
							} while(!email_control);
							adicionar_log_dinamico(logs, "Email validado");
							break;
						case 7:
						    printf(CYAN   "     0) " YELLOW "Nenhum" RESET);
							printf(CYAN   "     1) " BLUE   "Mouse" RESET);
							printf(CYAN   "     2) " GREEN  "Teclado" RESET);
							printf(CYAN   "     3) " BOLD   "Cabo HDMI" RESET);
							printf(CYAN   "     4) " BOLD   "Monitor" RESET);
							printf(CYAN   "     5) " BOLD   "Impressora" RESET);
							printf(CYAN   "     6) " BOLD   "Notebook" RESET);
							printf(CYAN   "     7) " BOLD   "Cabo de rede" RESET);
							printf(CYAN   "     8) " BOLD   "Webcam" RESET);
							printf(CYAN   "     9) " BOLD   "Fone de ouvido" RESET);

						    do {
                                printf(CYAN  " [5] " RED "--> " RESET);
                                scanf_control = scanf("%d", &item);
                                
                                //Verifica o item
                                if (scanf_control == 1 && item >= 0 && item <= 9) {
                                    printf(YELLOW  "%d\n" RESET, item);
                                    switch (item) {
                                        case 0:  call_data->item = NONE; call_data->qtd_item = 0; break;
                                        case 1:  call_data->item = MOUSE;       break;
                                        case 2:  call_data->item = KEYBOARD;    break;
                                        case 3:  call_data->item = CABO_HDMI;   break;
                                        case 4:  call_data->item = MONITOR;     break;
                                        case 5:  call_data->item = IMPRESSORA;  break;
                                        case 6:  call_data->item = NOTEBOOK;    break;
                                        case 7:  call_data->item = CABO_REDE;   break;
                                        case 8:  call_data->item = WEBCAM;      break;
                                        case 9:  call_data->item = HEADSET;     break;
                                        default: call_data->item = NONE; call_data->qtd_item = 0; break;
                                    }
                                } else {
                                    printf(RED  " --> Item inválido\n" RESET);
                                }
                        
                                clean_buffer_stdin();
                            } while (!(scanf_control == 1 && item >= 0 && item <= 9));
                            adicionar_log_dinamico(logs, "Item validado.");
                            break;
						case 8:
						    if (call_data->item != NONE) {
                                do {
                                    printf(CYAN  " [6] " RED "--> " RESET);
                                    scanf_control = scanf("%d", &qtd_item);
                                    
                                    if (qtd_item == 0) {
                                        do {
                                            printf(RED  " --> Você informou um item no índice anterior. Tem certeza de que não deseja solicitá-lo mais? (S/N)\n" RESET);
                                            printf(CYAN "\n  --> " RESET);
                                            scanf_control = scanf(" %c", &resposta_sn);
                                            clean_buffer_stdin();
                                            
                                            resposta_sn = toupper(resposta_sn);
                                        
                                            if (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N')) {
                                                printf(RED "Entrada inválida. Digite 'S' para Sim ou 'N' para Não.\n" RESET);
                                            }
                                        } while (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N'));
                                        
                                        if (resposta_sn == 'S') {
                                            call_data->item = NONE;
                                            call_data->qtd_item = 0;
                                            break;
                                        } else continue;
                                    } else if (qtd_item < 0) {
                                        printf(RED "A quantidade não pode ser um valor negativo.\n" RESET);
                                    } else if (qtd_item > 10) {
                                        printf(RED "Valor inserido acima do limite de solicitação (10).\n" RESET);
                                    } else call_data->qtd_item = qtd_item;
                                    
                                    clean_buffer_stdin();
                                } while (!(scanf_control == 1 && (qtd_item > 0 && qtd_item <= 10) || call_data->item == NONE));
                                adicionar_log_dinamico(logs, "Quantidade do item validado.");
                            } else {
                                printf(RED "Não há itens solicitados.\n" RESET);
                            }
						    break;
						case 9:
							printf(CYAN  " [7] " RED "--> " RESET);
							scanf(" %1023[^\n]", call_data->desc);
							clean_buffer_stdin();
							break;
						case 10:
							printf(CYAN  " [8] " RED "--> " RESET);
							scanf(" %1023[^\n]", call_data->solution);
							clean_buffer_stdin();
							break;
						}
					} else {
						switch (index_control) {
						case 1:

							printf(CYAN  " [1] " RED "--> " RESET);
							scanf(" %149[^\n]", call_data->title);
							clean_buffer_stdin();
							break;
						case 2:
							do {
								printf(CYAN   "     0) " BLUE "Baixa" RESET);
								printf(CYAN   "     1) " YELLOW "MC)dia" RESET);
								printf(CYAN   "     2) " RED "Alta" RESET);
								printf(CYAN   "     3) " BOLD RED "Urgente\n" RESET);

								printf(CYAN  " [2] " RED "--> " RESET);
								scanf_control = scanf("%d", &priority);

								//Verifica priority
								if (scanf_control == 1 && priority >= 0 && priority <= 3) {
									switch (priority) {
									case 0:
										call_data->priority = BAIXA;
										break;
									case 1:
										call_data->priority = MEDIA;
										break;
									case 2:
										call_data->priority = ALTA;
										break;
									case 3:
										call_data->priority = URGENTE;
										break;
									default:
										call_data->priority = BAIXA;
										break;
									}
									priority_control = 1;
								} else {
									printf(RED  " --> priority invC!lido\n" RESET);
								}

								clean_buffer_stdin();
							} while (!(scanf_control && priority_control));
							adicionar_log_dinamico(logs, "priority validado!");
							break;
						case 3:
							printf(CYAN  " [3] " RED "--> " RESET);
							scanf(" %99[^\n]", call_data->name);
							clean_buffer_stdin();
							break;
						case 4:
							do {
								printf(CYAN  " [4] " RED "--> " RESET);
								scanf(" %99[^\n]", email);
								clean_buffer_stdin();

								char* arroba = strchr(email, '@');
								char* dot = strchr(email, '.');

								//Verifica email
								if (!(arroba == NULL || dot == NULL)) {
									strcpy(call_data->email, email);
									email_control = 1;
								} else {
									printf(RED  " --> Email invC!lido\n" RESET);
								}
							} while(!email_control);
							adicionar_log_dinamico(logs, "Email validado");
							break;
						case 5:
						    printf(CYAN   "     0) " YELLOW "Nenhum" RESET);
							printf(CYAN   "     1) " BLUE   "Mouse" RESET);
							printf(CYAN   "     2) " GREEN  "Teclado" RESET);
							printf(CYAN   "     3) " BOLD   "Cabo HDMI" RESET);
							printf(CYAN   "     4) " BOLD   "Monitor" RESET);
							printf(CYAN   "     5) " BOLD   "Impressora" RESET);
							printf(CYAN   "     6) " BOLD   "Notebook" RESET);
							printf(CYAN   "     7) " BOLD   "Cabo de rede" RESET);
							printf(CYAN   "     8) " BOLD   "Webcam" RESET);
							printf(CYAN   "     9) " BOLD   "Fone de ouvido" RESET);

						    do {
                                printf(CYAN  " [5] " RED "--> " RESET);
                                scanf_control = scanf("%d", &item);
                                
                                //Verifica o item
                                if (scanf_control == 1 && item >= 0 && item <= 9) {
                                    printf(YELLOW  "%d\n" RESET, item);
                                    switch (item) {
                                        case 0:  call_data->item = NONE;        break;
                                        case 1:  call_data->item = MOUSE;       break;
                                        case 2:  call_data->item = KEYBOARD;    break;
                                        case 3:  call_data->item = CABO_HDMI;   break;
                                        case 4:  call_data->item = MONITOR;     break;
                                        case 5:  call_data->item = IMPRESSORA;  break;
                                        case 6:  call_data->item = NOTEBOOK;    break;
                                        case 7:  call_data->item = CABO_REDE;   break;
                                        case 8:  call_data->item = WEBCAM;      break;
                                        case 9:  call_data->item = HEADSET;     break;
                                        default: call_data->item = NONE;        break;
                                    }
                                } else {
                                    printf(RED  " --> Item inválido\n" RESET);
                                }
                        
                                clean_buffer_stdin();
                            } while (!(scanf_control == 1 && item >= 0 && item <= 9));
                            adicionar_log_dinamico(logs, "Item validado.");
                            break;
						case 6:
						    if (call_data->item != NONE) {
                                do {
                                    printf(CYAN  " [6] " RED "--> " RESET);
                                    scanf_control = scanf("%d", &qtd_item);
                                    
                                    if (qtd_item == 0) {
                                        do {
                                            printf(RED  " --> Você informou um item no índice anterior. Tem certeza de que não deseja solicitá-lo mais? (S/N)\n" RESET);
                                            printf(CYAN "\n  --> " RESET);
                                            scanf_control = scanf(" %c", &resposta_sn);
                                            clean_buffer_stdin();
                                            
                                            resposta_sn = toupper(resposta_sn);
                                        
                                            if (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N')) {
                                                printf(RED "Entrada inválida. Digite 'S' para Sim ou 'N' para Não.\n" RESET);
                                            }
                                        } while (scanf_control != 1 || (resposta_sn != 'S' && resposta_sn != 'N'));
                                        
                                        if (resposta_sn == 'S') {
                                            call_data->item = NONE;
                                            call_data->qtd_item = 0;
                                            break;
                                        } else continue;
                                    } else if (qtd_item < 0) {
                                        printf(RED "A quantidade não pode ser um valor negativo.\n" RESET);
                                    } else if (qtd_item > 10) {
                                        printf(RED "Valor inserido acima do limite de solicitação (10).\n" RESET);
                                    } else call_data->qtd_item = qtd_item;
                                    
                                    clean_buffer_stdin();
                                } while (!(scanf_control == 1 && (qtd_item > 0 && qtd_item <= 10) || call_data->item == NONE));
                                adicionar_log_dinamico(logs, "Quantidade do item validado.");
                            } else {
                                printf(RED "Não há itens solicitados.\n" RESET);
                            }
						    break;
						case 7:
							printf(CYAN  " [7] " RED "--> " RESET);
							scanf(" %1023[^\n]", call_data->desc);
							clean_buffer_stdin();
							break;
						}
					}
				} else {
					printf(RED  " --> Index invC!lido\n" RESET);
				}

			} while (!(scanf_control && index_control > 0 && index_control <= index));
		}

		call_data->updated_at = time(NULL);

		// Atualiza o dado na sua fila raiz (fifo ou heap)
		if (call_list_heap != NULL) {
			for (int i = 0; i < call_list_heap->size; i++) {
				if (call_list_heap->data[i].id == selected_id) {
					if (cancel_control) {
						heap_remove(call_list_heap, logs);
						adicionar_log_dinamico(logs, "Chamado removido da lista Heap.");
					} else {
						call_list_heap->data[i] = *call_data;
						adicionar_log_dinamico(logs, "Chamado atualizado na lista Heap.");
					}
					search_control = 1;
					break;
				}
			}
		}

		if (!search_control && call_list_fifo != NULL) {
			for (int i = 0; i < call_list_fifo->size; i++) {
				int index = (call_list_fifo->front + i) % call_list_fifo->capacity;
				if (call_list_fifo->data[index].id == selected_id) {
					if (cancel_control) {
						fifo_dequeue(call_list_fifo, logs);
						adicionar_log_dinamico(logs, "Chamado removido da fila FIFO.");
					} else {
						call_list_fifo->data[i] = *call_data;
						adicionar_log_dinamico(logs, "Chamado atualizado na fila FIFO.");
					}
					search_control = 1;
					break;
				}
			}
		}
		
		if (!search_control && call_suspend != NULL && call_suspend->head != NULL) {
            CallNode *current_node = call_suspend->head;
            while (current_node != NULL) {
                if (current_node->data->id == selected_id) {
                    if (cancel_control) {
                        if (remover_call_service(call_suspend, selected_id)) {
                            adicionar_log_dinamico(logs, "Chamado removido da lista Suspensa.");
                        }
                    } else {
                        *(current_node->data) = *call_data;
                        adicionar_log_dinamico(logs, "Chamado atualizado na lista Suspensa.");
                    }
                    search_control = 1;
                    break;
                }
                current_node = current_node->next;
            }
        }
        
        if (!search_control && arv_tec != NULL && arv_tec->raiz != NULL) {
             int resultado_arvore = buscar_e_atualizar_lista_tecnico(arv_tec->raiz, call_data, selected_id, cancel_control, logs);
            if (resultado_arvore) {
                search_control = 1;
            }
        }
		

		if (cancel_control) return 9998;

		clear();
	}
}