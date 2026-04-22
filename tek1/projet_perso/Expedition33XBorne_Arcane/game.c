/*
** EPITECH PROJECT, 2026
** game design
** File description:
** expedition 33 X borne d'arcane
*/

#include "game.h"
//utils
static float randf(float lo, float hi) {
    return lo + (hi - lo) * ((float)rand() / RAND_MAX);
}

static int recti_overlap(float ax, float ay, int aw, int ah,
                          float bx, float by, int bw, int bh) {
    return ax < bx+bw && ax+aw > bx && ay < by+bh && ay+ah > by;
}

//particule
static void spawn_particles(Game* g, float x, float y, int n,
                             float r, float gr, float b,
                             float speed, int life) {
    for (int i = 0; i < n; i++) {
        for (int p = 0; p < MAX_PARTICLES; p++) {
            if (g->particles[p].life <= 0) {
                float angle = randf(0, 2.0f * 3.14159f);
                float spd   = randf(speed * 0.4f, speed);
                g->particles[p].x       = x;
                g->particles[p].y       = y;
                g->particles[p].vx      = cosf(angle) * spd;
                g->particles[p].vy      = sinf(angle) * spd - randf(0, 2);
                g->particles[p].r       = r;
                g->particles[p].g       = gr;
                g->particles[p].b       = b;
                g->particles[p].a       = 255;
                g->particles[p].life    = life + rand() % (life/2+1);
                g->particles[p].max_life= g->particles[p].life;
                break;
            }
        }
    }
}

static void update_particles(Game* g) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle* p = &g->particles[i];
        if (p->life <= 0) continue;
        p->x  += p->vx;
        p->y  += p->vy;
        p->vy += 0.12f;
        p->vx *= 0.97f;
        p->a   = 255.0f * p->life / p->max_life;
        p->life--;
    }
}

static void draw_particles(Game* g) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle* p = &g->particles[i];
        if (p->life <= 0) continue;
        SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(g->renderer,
            (Uint8)p->r, (Uint8)p->g, (Uint8)p->b, (Uint8)p->a);
        SDL_Rect r = {(int)(p->x + g->cam_ox) - 3,
                      (int)(p->y + g->cam_oy) - 3, 6, 6};
        SDL_RenderFillRect(g->renderer, &r);
    }
    SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_NONE);
}

//initialisation game
static void init_platforms(Game* g) {
    // Sol
    g->platforms[0] = (Platform){0, SCREEN_H - 50, SCREEN_W, 50};
    g->num_platforms = 1;

    // Plateformes fixes — paysage de Lumière Obscure
    Platform lvl[] = {
        {100,  430, 180, 20},
        {350,  370, 200, 20},
        {620,  430, 180, 20},
        {200,  290, 150, 20},
        {500,  250, 160, 20},
        {720,  310, 140, 20},
        {  0,  200, 120, 20},
        {780,  200, 120, 20},
        {380,  160, 140, 20},
    };
    int n = sizeof(lvl)/sizeof(lvl[0]);
    for (int i = 0; i < n && g->num_platforms < MAX_PLATFORMS; i++) {
        g->platforms[g->num_platforms++] = lvl[i];
    }
}

static void init_stars(Game* g) {
    for (int i = 0; i < 80; i++) {
        g->stars[i].x     = randf(0, SCREEN_W);
        g->stars[i].y     = randf(0, SCREEN_H * 0.7f);
        g->stars[i].blink = randf(0, 6.28f);
    }
}

static void init_player(Game* g) {
    g->player.x         = 100;
    g->player.y         = SCREEN_H - 150;
    g->player.vx        = 0;
    g->player.vy        = 0;
    g->player.hp        = 6;
    g->player.max_hp    = 6;
    g->player.on_ground = 0;
    g->player.attack_cd = 0;
    g->player.paint_cd  = 0;
    g->player.invincible= 0;
    g->player.anim_tick = 0;
    g->player.dir       = DIR_RIGHT;
    g->player.is_attacking = 0;
    g->player.attack_anim  = 0;
}

static void spawn_wave(Game* g) {
    g->wave++;
    int count = 3 + g->wave * 2;
    if (count > MAX_ENEMIES) count = MAX_ENEMIES;
    g->enemies_left = count;

    for (int i = 0; i < MAX_ENEMIES; i++) g->enemies[i].active = 0;

    for (int i = 0; i < count; i++) {
        Enemy* e   = &g->enemies[i];
        e->active  = 1;
        e->type    = (i % 3 == 2) ? 1 : 0;
        e->x       = (i % 2 == 0) ? randf(SCREEN_W - 200, SCREEN_W - 20)
                                   : randf(20, 200);
        e->y       = 50;
        e->vx      = 0;
        e->vy      = 0;
        e->hp      = (e->type == 1) ? 3 : 2;
        e->max_hp  = e->hp;
        e->dir     = DIR_LEFT;
        e->on_ground   = 0;
        e->anim_tick   = rand() % 60;
        e->aggro_range = 350.0f;
        e->attack_cd   = 0;
    }
}

//logique of game
static void fire_bullet(Game* g, float x, float y, float vx, float vy,
                         int is_paint) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!g->bullets[i].active) {
            g->bullets[i].active   = 1;
            g->bullets[i].x        = x;
            g->bullets[i].y        = y;
            g->bullets[i].vx       = vx;
            g->bullets[i].vy       = vy;
            g->bullets[i].is_paint = is_paint;
            g->bullets[i].angle    = 0;
            return;
        }
    }
}

static void resolve_platform_collision(float* px, float* py,
                                       float* pvy, int pw, int ph,
                                       int* on_ground,
                                       Platform* plats, int np) {
    *on_ground = 0;
    for (int i = 0; i < np; i++) {
        Platform* pl = &plats[i];
        if (recti_overlap(*px, *py, pw, ph,
                          pl->x, pl->y, pl->w, pl->h)) {
            // Collision par le haut
            float prev_bottom = *py + ph - *pvy;
            if (prev_bottom <= pl->y + 4 && *pvy >= 0) {
                *py       = pl->y - ph;
                *pvy      = 0;
                *on_ground = 1;
            }
            // Collision par le bas
            else if (*pvy < 0) {
                *py  = pl->y + pl->h;
                *pvy = 0;
            }
        }
    }
}

static void update_player(Game* g, const Uint8* keys) {
    Player* p = &g->player;

    // Déplacement horizontal
    p->vx = 0;
    if (keys[SDL_SCANCODE_LEFT]  || keys[SDL_SCANCODE_A]) {
        p->vx = -PLAYER_SPEED; p->dir = DIR_LEFT;
    }
    if (keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_D]) {
        p->vx = PLAYER_SPEED;  p->dir = DIR_RIGHT;
    }

    // Saut
    if ((keys[SDL_SCANCODE_UP] || keys[SDL_SCANCODE_W] ||
         keys[SDL_SCANCODE_SPACE]) && p->on_ground) {
        p->vy = JUMP_FORCE;
    }

    // Attaque épée (touche X ou LCTRL)
    if ((keys[SDL_SCANCODE_X] || keys[SDL_SCANCODE_LCTRL]) && p->attack_cd == 0) {
        p->is_attacking = 1;
        p->attack_anim  = 14;
        p->attack_cd    = 25;
        spawn_particles(g, p->x + 30*(int)p->dir, p->y+10,
                        12, 200,220,255, 5, 12);
        g->cam_shake = 4;
    }

    // Sort peinture (touche W ou SHIFT)
    if ((keys[SDL_SCANCODE_Z] || keys[SDL_SCANCODE_LSHIFT]) && p->paint_cd == 0) {
        float bvx = BULLET_SPEED * p->dir;
        fire_bullet(g, p->x + 16 + 16*(int)p->dir, p->y + 12, bvx, -2, 1);
        p->paint_cd = 30;
        spawn_particles(g, p->x+16, p->y+12, 8, 255,100,220, 4, 10);
    }

    // Physique
    p->vy += GRAVITY;
    p->x  += p->vx;
    p->y  += p->vy;

    // Bords écran
    if (p->x < 0)            p->x = 0;
    if (p->x > SCREEN_W - 32) p->x = SCREEN_W - 32;
    if (p->y > SCREEN_H)      { p->hp = 0; return; } /* tombé dans le vide */

    resolve_platform_collision(&p->x, &p->y, &p->vy, 32, 48,
                               &p->on_ground, g->platforms, g->num_platforms);

    // Cooldowns
    if (p->attack_cd  > 0) p->attack_cd--;
    if (p->paint_cd   > 0) p->paint_cd--;
    if (p->invincible > 0) p->invincible--;
    if (p->attack_anim> 0) { p->attack_anim--; if(!p->attack_anim) p->is_attacking=0; }
    p->anim_tick++;

    // Hitbox épée
    if (p->is_attacking) {
        float sx = p->x + (p->dir == DIR_RIGHT ? 32 : -60);
        float sy = p->y + 8;
        for (int i = 0; i < MAX_ENEMIES; i++) {
            Enemy* e = &g->enemies[i];
            if (!e->active) continue;
            if (recti_overlap(sx, sy, 60, 32, e->x, e->y, 32, 48)) {
                e->hp--;
                e->vx = 5.0f * p->dir;
                e->vy = -5;
                spawn_particles(g, e->x+16, e->y+24, 16, 220,80,40, 5, 18);
                g->cam_shake = 6;
                g->score    += 10;
                if (e->hp <= 0) {
                    e->active = 0;
                    g->enemies_left--;
                    spawn_particles(g, e->x+16, e->y+24, 30,
                                    200,100,255, 7, 25);
                    g->score += 50;
                }
            }
        }
    }
}

static void update_bullets(Game* g) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet* b = &g->bullets[i];
        if (!b->active) continue;

        b->x     += b->vx;
        b->y     += b->vy;
        b->vy    += 0.15f;
        b->angle += 0.2f;

        // Sillage de peinture
        if (b->is_paint && g->tick % 2 == 0)
            spawn_particles(g, b->x, b->y, 3, 255,120,220, 1.5f, 8);

        // Hors écran
        if (b->x < -20 || b->x > SCREEN_W+20 ||
            b->y < -20 || b->y > SCREEN_H+20) {
            b->active = 0; continue;
        }

        // Collision sol/plateformes
        for (int p = 0; p < g->num_platforms; p++) {
            Platform* pl = &g->platforms[p];
            if (b->x > pl->x && b->x < pl->x+pl->w &&
                b->y > pl->y && b->y < pl->y+pl->h) {
                spawn_particles(g, b->x, b->y, 10, 255,100,200, 3, 12);
                b->active = 0; break;
            }
        }
        if (!b->active) continue;

        // Collision ennemis
        for (int e = 0; e < MAX_ENEMIES; e++) {
            Enemy* en = &g->enemies[e];
            if (!en->active) continue;
            if (recti_overlap(b->x-6, b->y-6, 12, 12, en->x, en->y, 32, 48)) {
                en->hp--;
                en->vx = b->vx * 0.5f;
                en->vy = -4;
                spawn_particles(g, en->x+16, en->y+24, 14, 255,100,200, 5, 18);
                b->active = 0;
                g->score += 10;
                if (en->hp <= 0) {
                    en->active = 0;
                    g->enemies_left--;
                    spawn_particles(g, en->x+16, en->y+24, 30,
                                    200,100,255, 7, 25);
                    g->score += 50;
                }
                break;
            }
        }
    }
}

static void update_enemies(Game* g) {
    Player* p = &g->player;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy* e = &g->enemies[i];
        if (!e->active) continue;

        e->anim_tick++;

        float dx = p->x - e->x;
        float dy = p->y - e->y;
        float dist = sqrtf(dx*dx + dy*dy);

        if (dist < e->aggro_range) {
            // Poursuite
            float spd = (e->type == 1) ? ENEMY_SPEED * 1.4f : ENEMY_SPEED;
            e->vx = (dx > 0 ? 1 : -1) * spd;
            e->dir = (dx > 0) ? DIR_RIGHT : DIR_LEFT;

            // Fantôme : vol
            if (e->type == 1) {
                e->vy = (dy > 0 ? 1 : -1) * spd * 0.7f;
            }
        } else {
            e->vx *= 0.8f;
        }

        // Gravité (soldats seulement)
        if (e->type == 0) {
            e->vy += GRAVITY;
        }

        e->x += e->vx;
        e->y += e->vy;

        /* Bords */
        if (e->x < 0)             e->x = 0;
        if (e->x > SCREEN_W - 32)  e->x = SCREEN_W - 32;

        if (e->type == 0) {
            resolve_platform_collision(&e->x, &e->y, &e->vy, 32, 48,
                                       &e->on_ground, g->platforms, g->num_platforms);
        }

        // Attaque joueur
        if (dist < 50 && e->attack_cd == 0 && p->invincible == 0) {
            p->hp--;
            p->invincible = 60;
            e->attack_cd  = 90;
            p->vx = -8.0f * e->dir;
            p->vy = -6;
            spawn_particles(g, p->x+16, p->y+24, 20, 220,60,60, 5, 20);
            g->cam_shake = 8;
        }
        if (e->attack_cd > 0) e->attack_cd--;
    }
}

//sprite and/or draw all
static void draw_gradient_bg(Game* g) {
    for (int y = 0; y < SCREEN_H; y++) {
        float t = (float)y / SCREEN_H;
        Uint8 r = (Uint8)(10  + t * 15);
        Uint8 gr= (Uint8)(8   + t * 7);
        Uint8 b = (Uint8)(28  + t * 22);
        SDL_SetRenderDrawColor(g->renderer, r, gr, b, 255);
        SDL_RenderDrawLine(g->renderer, 0, y, SCREEN_W, y);
    }
}

static void draw_stars(Game* g) {
    SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < 80; i++) {
        Star* s = &g->stars[i];
        s->blink += 0.04f;
        Uint8 a = (Uint8)(180 + 75 * sinf(s->blink));
        SDL_SetRenderDrawColor(g->renderer, 255, 240, 200, a);
        SDL_Rect r = {(int)s->x, (int)s->y, 2, 2};
        SDL_RenderFillRect(g->renderer, &r);
    }
    SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_NONE);
}

static void draw_platforms(Game* g) {
    for (int i = 0; i < g->num_platforms; i++) {
        Platform* pl = &g->platforms[i];
        int ox = (int)g->cam_ox, oy = (int)g->cam_oy;

        // Corps
        SDL_SetRenderDrawColor(g->renderer, 60, 40, 100, 255);
        SDL_Rect body = {(int)pl->x+ox, (int)pl->y+4+oy, pl->w, pl->h};
        SDL_RenderFillRect(g->renderer, &body);

        // Bord supérieur lumineux
        SDL_SetRenderDrawColor(g->renderer, 140, 100, 200, 255);
        SDL_Rect top = {(int)pl->x+ox, (int)pl->y+oy, pl->w, 4};
        SDL_RenderFillRect(g->renderer, &top);

        // Reflet dégradé
        SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(g->renderer, 180, 140, 255, 60);
        SDL_Rect shine = {(int)pl->x+ox+4, (int)pl->y+oy, pl->w-8, 2};
        SDL_RenderFillRect(g->renderer, &shine);
        SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_NONE);
    }
}

// Dessin de Gustave pixel-art, param gustave
static void draw_player(Game* g) {
    Player* p = &g->player;
    int ox = (int)g->cam_ox, oy = (int)g->cam_oy;
    int px = (int)p->x + ox;
    int py = (int)p->y + oy;
    int fl = (p->dir == DIR_LEFT);

    // Clignotement si invincible
    if (p->invincible > 0 && (g->tick % 6) < 3) return;

    // Corps / manteau rouge
    SDL_SetRenderDrawColor(g->renderer, 180, 60, 60, 255);
    SDL_Rect coat = {px+4, py+16, 24, 28};
    SDL_RenderFillRect(g->renderer, &coat);

    // Tête
    SDL_SetRenderDrawColor(g->renderer, 220, 190, 80, 255);
    SDL_Rect head = {px+8, py+2, 16, 14};
    SDL_RenderFillRect(g->renderer, &head);

    // Cheveux
    SDL_SetRenderDrawColor(g->renderer, 80, 50, 20, 255);
    SDL_Rect hair = {px+8, py+2, 16, 6};
    SDL_RenderFillRect(g->renderer, &hair);

    // Jambes (animées)
    int leg_off = (int)(sinf(p->anim_tick * 0.3f) * 4);
    SDL_SetRenderDrawColor(g->renderer, 40, 30, 70, 255);
    SDL_Rect leg1 = {px+6,  py+44, 8, 12 + (p->on_ground ? leg_off : 0)};
    SDL_Rect leg2 = {px+18, py+44, 8, 12 - (p->on_ground ? leg_off : 0)};
    SDL_RenderFillRect(g->renderer, &leg1);
    SDL_RenderFillRect(g->renderer, &leg2);

    // Bras
    SDL_SetRenderDrawColor(g->renderer, 180, 60, 60, 255);
    int barm_off = fl ? px+22 : px+2;
    SDL_Rect arm = {barm_off, py+18, 8, 18};
    SDL_RenderFillRect(g->renderer, &arm);

    // Épée (bras actif)
    SDL_SetRenderDrawColor(g->renderer, 200, 220, 255, 255);
    if (fl) {
        SDL_Rect sword = {px - (p->is_attacking ? 40 : 10), py+14, 36, 6};
        SDL_RenderFillRect(g->renderer, &sword);
    } else {
        SDL_Rect sword = {px + (p->is_attacking ? 28 : 0), py+14, 36, 6};
        SDL_RenderFillRect(g->renderer, &sword);
    }

    // Flash attaque
    if (p->is_attacking) {
        SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(g->renderer, 200, 220, 255, 80);
        SDL_Rect flash = {fl ? px-50 : px+10, py, 60, 40};
        SDL_RenderFillRect(g->renderer, &flash);
        SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_NONE);
    }
}

static void draw_enemies(Game* g) {
    int ox = (int)g->cam_ox, oy = (int)g->cam_oy;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy* e = &g->enemies[i];
        if (!e->active) continue;

        int ex = (int)e->x + ox;
        int ey = (int)e->y + oy;
        int fl = (e->dir == DIR_LEFT);
        float bob = sinf(e->anim_tick * 0.08f) * 3;

        if (e->type == 0) {
            // Soldat Peintre
            // Corps
            SDL_SetRenderDrawColor(g->renderer, 80, 40, 20, 255);
            SDL_Rect body = {ex+4, ey+16, 24, 28};
            SDL_RenderFillRect(g->renderer, &body);
            // Tête
            SDL_SetRenderDrawColor(g->renderer, 200, 80, 40, 255);
            SDL_Rect head = {ex+7, (int)(ey+2+bob), 18, 14};
            SDL_RenderFillRect(g->renderer, &head);
            // Yeux blancs
            SDL_SetRenderDrawColor(g->renderer, 240, 240, 240, 255);
            SDL_Rect eye1 = {ex+ (fl?10:18), (int)(ey+6+bob), 4, 4};
            SDL_RenderFillRect(g->renderer, &eye1);
            // Bras
            SDL_SetRenderDrawColor(g->renderer, 80, 40, 20, 255);
            SDL_Rect arm = {fl ? ex+22 : ex+2, ey+18, 8, 20};
            SDL_RenderFillRect(g->renderer, &arm);
        } else {
            // Fantôme
            SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(g->renderer, 100, 40, 160, 160);
            SDL_Rect body = {ex+2, (int)(ey+bob), 28, 40};
            SDL_RenderFillRect(g->renderer, &body);
            // Visage
            SDL_SetRenderDrawColor(g->renderer, 180, 120, 255, 200);
            SDL_Rect face = {ex+6, (int)(ey+4+bob), 20, 16};
            SDL_RenderFillRect(g->renderer, &face);
            // Yeux violets lumineux
            SDL_SetRenderDrawColor(g->renderer, 220, 180, 255, 255);
            SDL_Rect ey1 = {ex+(fl?9:19), (int)(ey+8+bob), 5, 5};
            SDL_RenderFillRect(g->renderer, &ey1);
            //aura
            SDL_SetRenderDrawColor(g->renderer, 140, 80, 220, 40);
            SDL_Rect aura = {ex-6, (int)(ey-4+bob), 44, 52};
            SDL_RenderFillRect(g->renderer, &aura);
            SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_NONE);
        }

        //life enemy
        int bar_w = 32;
        int bar_h = 4;
        SDL_SetRenderDrawColor(g->renderer, 60, 20, 20, 255);
        SDL_Rect hbg = {ex, ey-8, bar_w, bar_h};
        SDL_RenderFillRect(g->renderer, &hbg);
        int filled = bar_w * e->hp / e->max_hp;
        SDL_SetRenderDrawColor(g->renderer, 220, 60, 60, 255);
        SDL_Rect hfg = {ex, ey-8, filled, bar_h};
        SDL_RenderFillRect(g->renderer, &hfg);
    }
}

static void draw_bullets(Game* g) {
    int ox = (int)g->cam_ox, oy = (int)g->cam_oy;

    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet* b = &g->bullets[i];
        if (!b->active) continue;

        int bx = (int)b->x + ox;
        int by = (int)b->y + oy;

        if (b->is_paint) {
            // Orbe de peinture(atk dist)
            SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(g->renderer, 255, 80, 200, 200);
            SDL_Rect orb = {bx-7, by-7, 14, 14};
            SDL_RenderFillRect(g->renderer, &orb);
            SDL_SetRenderDrawColor(g->renderer, 255, 200, 240, 100);
            SDL_Rect glow = {bx-11, by-11, 22, 22};
            SDL_RenderFillRect(g->renderer, &glow);
            SDL_SetRenderDrawBlendMode(g->renderer, SDL_BLENDMODE_NONE);
        }
    }
}

static void draw_hud(Game* g) {
    Player* p = &g->player;

    // life of player (Gustave)
    SDL_SetRenderDrawColor(g->renderer, 20, 10, 40, 200);
    SDL_Rect hud_bg = {10, 10, 200, 22};
    SDL_RenderFillRect(g->renderer, &hud_bg);

    SDL_SetRenderDrawColor(g->renderer, 60, 20, 20, 255);
    SDL_Rect hp_bg = {14, 14, 192, 14};
    SDL_RenderFillRect(g->renderer, &hp_bg);

    int hp_w = 192 * p->hp / p->max_hp;
    SDL_SetRenderDrawColor(g->renderer, 220, 60, 60, 255);
    SDL_Rect hp_fg = {14, 14, hp_w, 14};
    SDL_RenderFillRect(g->renderer, &hp_fg);

    // life sprite
    for (int i = 0; i < p->max_hp; i++) {
        int hx = 16 + i * 32;
        SDL_SetRenderDrawColor(g->renderer,
            i < p->hp ? 255 : 80,
            i < p->hp ? 80 : 40, 80, 255);
        SDL_Rect heart = {hx, 30, 10, 10};
        SDL_RenderFillRect(g->renderer, &heart);
    }

    // Score
    if (g->font_med) {
        char buf[64];
        snprintf(buf, sizeof(buf), "SCORE: %05d", g->score);
        SDL_Color wh = {255, 240, 200, 255};
        SDL_Surface* sf = TTF_RenderText_Blended(g->font_med, buf, wh);
        if (sf) {
            SDL_Texture* tx = SDL_CreateTextureFromSurface(g->renderer, sf);
            if (tx) {
                SDL_Rect dr = {SCREEN_W - sf->w - 14, 10, sf->w, sf->h};
                SDL_RenderCopy(g->renderer, tx, NULL, &dr);
                SDL_DestroyTexture(tx);
            }
            SDL_FreeSurface(sf);
        }

        // Vague
        snprintf(buf, sizeof(buf), "VAGUE %d  |  Ennemis: %d", g->wave, g->enemies_left);
        SDL_Surface* sf2 = TTF_RenderText_Blended(g->font_sm, buf, wh);
        if (sf2) {
            SDL_Texture* tx2 = SDL_CreateTextureFromSurface(g->renderer, sf2);
            if (tx2) {
                SDL_Rect dr2 = {SCREEN_W/2 - sf2->w/2, 10, sf2->w, sf2->h};
                SDL_RenderCopy(g->renderer, tx2, NULL, &dr2);
                SDL_DestroyTexture(tx2);
            }
            SDL_FreeSurface(sf2);
        }

        //Contrôles
        SDL_Color dim = {150, 130, 200, 200};
        SDL_Surface* sf3 = TTF_RenderText_Blended(g->font_sm,
            "Fleches/QD:Deplacer  SPACE/Z:Sauter  X/CTRL:Epee  W/SHIFT:Peinture", dim);
        if (sf3) {
            SDL_Texture* tx3 = SDL_CreateTextureFromSurface(g->renderer, sf3);
            if (tx3) {
                SDL_Rect dr3 = {SCREEN_W/2 - sf3->w/2, SCREEN_H - sf3->h - 6,
                                sf3->w, sf3->h};
                SDL_RenderCopy(g->renderer, tx3, NULL, &dr3);
                SDL_DestroyTexture(tx3);
            }
            SDL_FreeSurface(sf3);
        }
    }
}

static void draw_text_centered(Game* g, TTF_Font* font, const char* txt,
                               SDL_Color col, int y) {
    if (!font) return;
    SDL_Surface* sf = TTF_RenderText_Blended(font, txt, col);
    if (!sf) return;
    SDL_Texture* tx = SDL_CreateTextureFromSurface(g->renderer, sf);
    if (tx) {
        SDL_Rect dr = {SCREEN_W/2 - sf->w/2, y, sf->w, sf->h};
        SDL_RenderCopy(g->renderer, tx, NULL, &dr);
        SDL_DestroyTexture(tx);
    }
    SDL_FreeSurface(sf);
}

static void draw_menu(Game* g) {
    draw_gradient_bg(g);
    draw_stars(g);

    // Titre
    SDL_Color gold  = {220, 190,  80, 255};
    SDL_Color white = {255, 240, 200, 255};
    SDL_Color grey  = {150, 130, 200, 255};

    draw_text_centered(g, g->font_big, "EXPEDITION 33", gold, 80);
    draw_text_centered(g, g->font_med, "CLAIR OBSCUR - ARCADE", white, 160);

    // Séparateur
    SDL_SetRenderDrawColor(g->renderer, 140, 100, 200, 255);
    SDL_RenderDrawLine(g->renderer, 200, 205, 700, 205);

    draw_text_centered(g, g->font_sm,  "Affronte les serviteurs de la Peintre", grey, 230);
    draw_text_centered(g, g->font_sm,  "et survie jusqu'a la derniere vague!", grey, 255);

    // Bouton Start
    if ((g->tick / 30) % 2 == 0)
        draw_text_centered(g, g->font_med, ">> APPUIE SUR ENTREE <<", gold, 340);

    draw_text_centered(g, g->font_sm, "X / CTRL : Epee    W / SHIFT : Sort de Peinture", grey, 420);
    draw_text_centered(g, g->font_sm, "Fleches / QD : Deplacer    SPACE/Z : Sauter", grey, 445);

    //text on menu
    draw_text_centered(g, g->font_sm, "Inspire de Clair Obscur: Expedition 33 - Sandfall Interactive", grey, 540);
}

static void draw_gameover(Game* g) {
    draw_gradient_bg(g);
    draw_stars(g);

    SDL_Color red   = {220, 60,  60, 255};
    SDL_Color gold  = {220,190,  80, 255};
    SDL_Color grey  = {150,130, 200, 255};

    draw_text_centered(g, g->font_big, "EXPEDITION ECHOUEE", red, 100);

    char buf[64];
    snprintf(buf, sizeof(buf), "Score Final : %d", g->score);
    draw_text_centered(g, g->font_med, buf, gold, 220);

    snprintf(buf, sizeof(buf), "Vague atteinte : %d", g->wave);
    draw_text_centered(g, g->font_med, buf, gold, 265);

    if ((g->tick / 30) % 2 == 0)
        draw_text_centered(g, g->font_med, ">> ENTREE : Recommencer <<", gold, 360);

    draw_text_centered(g, g->font_sm, "ECHAP : Quitter", grey, 420);
}

static void draw_win(Game* g) {
    draw_gradient_bg(g);
    draw_stars(g);

    SDL_Color gold  = {220,190, 80, 255};
    SDL_Color white = {255,240,200, 255};
    SDL_Color grey  = {150,130,200, 255};

    draw_text_centered(g, g->font_big, "VICTOIRE !", gold, 80);
    draw_text_centered(g, g->font_med, "La Peintre a ete repoussee.", white, 190);

    char buf[64];
    snprintf(buf, sizeof(buf), "Score : %d", g->score);
    draw_text_centered(g, g->font_med, buf, gold, 250);

    if ((g->tick / 30) % 2 == 0)
        draw_text_centered(g, g->font_med, ">> ENTREE : Rejouer <<", gold, 360);
}

//boucle principale
Game* game_create(void) {
    srand((unsigned)time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return NULL;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return NULL;
    }

    Game* g = calloc(1, sizeof(Game));
    if (!g) return NULL;

    g->window = SDL_CreateWindow(
        "Expedition 33 - Arcade",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_W, SCREEN_H, 0);
    if (!g->window) {
        fprintf(stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
        free(g); return NULL;
    }

    g->renderer = SDL_CreateRenderer(g->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!g->renderer) {
        fprintf(stderr, "SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(g->window);
        free(g); return NULL;
    }

    //Polices
    const char* font_paths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf",
        "/usr/share/fonts/truetype/freefont/FreeSansBold.ttf",
        NULL
    };
    for (int i = 0; font_paths[i]; i++) {
        if (!g->font_big) g->font_big = TTF_OpenFont(font_paths[i], 52);
        if (!g->font_med) g->font_med = TTF_OpenFont(font_paths[i], 28);
        if (!g->font_sm)  g->font_sm  = TTF_OpenFont(font_paths[i], 16);
        if (g->font_big && g->font_med && g->font_sm) break;
    }

    g->state   = STATE_MENU;
    g->running = 1;
    g->score   = 0;
    g->wave    = 0;

    init_platforms(g);
    init_stars(g);
    init_player(g);

    return g;
}

void game_destroy(Game* g) {
    if (!g) return;
    if (g->font_big) TTF_CloseFont(g->font_big);
    if (g->font_med) TTF_CloseFont(g->font_med);
    if (g->font_sm)  TTF_CloseFont(g->font_sm);
    if (g->renderer) SDL_DestroyRenderer(g->renderer);
    if (g->window)   SDL_DestroyWindow(g->window);
    TTF_Quit();
    SDL_Quit();
    free(g);
}

static void start_game(Game* g) {
    g->score = 0;
    g->wave  = 0;
    init_player(g);
    memset(g->bullets,   0, sizeof(g->bullets));
    memset(g->particles, 0, sizeof(g->particles));
    spawn_wave(g);
    g->state = STATE_PLAYING;
}

void game_run(Game* g) {
    Uint32 frame_delay = 1000 / FPS;

    while (g->running) {
        Uint32 t0 = SDL_GetTicks();

        //Événements
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) {
                g->running = 0;
            }
            if (ev.type == SDL_KEYDOWN) {
                SDL_Scancode sc = ev.key.keysym.scancode;
                if (sc == SDL_SCANCODE_ESCAPE) g->running = 0;
                if (g->state == STATE_MENU &&
                    (sc == SDL_SCANCODE_RETURN || sc == SDL_SCANCODE_KP_ENTER))
                    start_game(g);
                if ((g->state == STATE_GAMEOVER || g->state == STATE_WIN) &&
                    (sc == SDL_SCANCODE_RETURN || sc == SDL_SCANCODE_KP_ENTER))
                    start_game(g);
            }
        }

        //update
        if (g->state == STATE_PLAYING) {
            const Uint8* keys = SDL_GetKeyboardState(NULL);

            /* Shake caméra */
            if (g->cam_shake > 0) {
                g->cam_ox = randf(-g->cam_shake, g->cam_shake);
                g->cam_oy = randf(-g->cam_shake, g->cam_shake);
                g->cam_shake--;
            } else {
                g->cam_ox = 0; g->cam_oy = 0;
            }

            update_player(g, keys);
            update_bullets(g);
            update_enemies(g);
            update_particles(g);

            //player dead ?
            if (g->player.hp <= 0) {
                spawn_particles(g, g->player.x+16, g->player.y+24,
                                50, 220,60,60, 8, 40);
                g->state = STATE_GAMEOVER;
            }

            //round is over ?
            if (g->enemies_left <= 0) {
                if (g->wave >= 5)
                    g->state = STATE_WIN;
                else
                    spawn_wave(g);
            }
        }

        //draw
        SDL_SetRenderDrawColor(g->renderer, 10, 8, 28, 255);
        SDL_RenderClear(g->renderer);

        switch (g->state) {
        case STATE_MENU:
            draw_menu(g);
            break;
        case STATE_PLAYING:
            draw_gradient_bg(g);
            draw_stars(g);
            draw_platforms(g);
            draw_particles(g);
            draw_bullets(g);
            draw_enemies(g);
            draw_player(g);
            draw_hud(g);
            break;
        case STATE_GAMEOVER:
            draw_gradient_bg(g);
            draw_stars(g);
            draw_particles(g);
            draw_gameover(g);
            update_particles(g);
            break;
        case STATE_WIN:
            draw_gradient_bg(g);
            draw_stars(g);
            draw_win(g);
            break;
        }

        SDL_RenderPresent(g->renderer);
        g->tick++;

        //timing
        Uint32 elapsed = SDL_GetTicks() - t0;
        if (elapsed < frame_delay)
            SDL_Delay(frame_delay - elapsed);
    }
}
