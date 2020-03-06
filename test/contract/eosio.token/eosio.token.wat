(module
  (type (;0;) (func))
  (type (;1;) (func (param i64)))
  (type (;2;) (func (param i32 i32)))
  (type (;3;) (func (param i64 i64 i64 i64) (result i32)))
  (type (;4;) (func (result i64)))
  (type (;5;) (func (param i32 i32 i32) (result i32)))
  (type (;6;) (func (param i64 i64 i64 i64 i32 i32) (result i32)))
  (type (;7;) (func (param i32 i64 i32 i32)))
  (type (;8;) (func (param i64) (result i32)))
  (type (;9;) (func (param i32 i32) (result i32)))
  (type (;10;) (func (result i32)))
  (type (;11;) (func (param i32 f32)))
  (type (;12;) (func (param i32 i64 i64 i64 i64)))
  (type (;13;) (func (param i32 f64)))
  (type (;14;) (func (param i64 i64) (result f64)))
  (type (;15;) (func (param i64 i64) (result f32)))
  (type (;16;) (func (param i64 i64) (result i32)))
  (type (;17;) (func (param i32 i64)))
  (type (;18;) (func (param i32)))
  (type (;19;) (func (param i64 i64 i64)))
  (type (;20;) (func (param i32) (result i32)))
  (type (;21;) (func (param i32 i32 i32)))
  (type (;22;) (func (param i32 i32 i32 i32)))
  (type (;23;) (func (param i32 i32 i64 i32)))
  (type (;24;) (func (param i32 i32 i32 i32 i32)))
  (type (;25;) (func (param i32 i64 i32) (result i32)))
  (type (;26;) (func (param i64 i64)))
  (import "env" "require_auth" (func (;0;) (type 1)))
  (import "env" "eosio_assert" (func (;1;) (type 2)))
  (import "env" "db_find_i64" (func (;2;) (type 3)))
  (import "env" "current_receiver" (func (;3;) (type 4)))
  (import "env" "abort" (func (;4;) (type 0)))
  (import "env" "memset" (func (;5;) (type 5)))
  (import "env" "db_store_i64" (func (;6;) (type 6)))
  (import "env" "db_update_i64" (func (;7;) (type 7)))
  (import "env" "memcpy" (func (;8;) (type 5)))
  (import "env" "is_account" (func (;9;) (type 8)))
  (import "env" "require_recipient" (func (;10;) (type 1)))
  (import "env" "has_auth" (func (;11;) (type 8)))
  (import "env" "db_next_i64" (func (;12;) (type 9)))
  (import "env" "action_data_size" (func (;13;) (type 10)))
  (import "env" "read_action_data" (func (;14;) (type 9)))
  (import "env" "memmove" (func (;15;) (type 5)))
  (import "env" "__extendsftf2" (func (;16;) (type 11)))
  (import "env" "__floatsitf" (func (;17;) (type 2)))
  (import "env" "__multf3" (func (;18;) (type 12)))
  (import "env" "__floatunsitf" (func (;19;) (type 2)))
  (import "env" "__divtf3" (func (;20;) (type 12)))
  (import "env" "__addtf3" (func (;21;) (type 12)))
  (import "env" "__extenddftf2" (func (;22;) (type 13)))
  (import "env" "__eqtf2" (func (;23;) (type 3)))
  (import "env" "__letf2" (func (;24;) (type 3)))
  (import "env" "__netf2" (func (;25;) (type 3)))
  (import "env" "__subtf3" (func (;26;) (type 12)))
  (import "env" "__trunctfdf2" (func (;27;) (type 14)))
  (import "env" "__getf2" (func (;28;) (type 3)))
  (import "env" "__trunctfsf2" (func (;29;) (type 15)))
  (import "env" "prints_l" (func (;30;) (type 2)))
  (import "env" "__unordtf2" (func (;31;) (type 3)))
  (import "env" "__fixunstfsi" (func (;32;) (type 16)))
  (import "env" "__fixtfsi" (func (;33;) (type 16)))
  (import "env" "eosio_assert_code" (func (;34;) (type 17)))
  (import "env" "db_get_i64" (func (;35;) (type 5)))
  (import "env" "db_remove_i64" (func (;36;) (type 18)))
  (func (;37;) (type 0)
    call 41)
  (func (;38;) (type 19) (param i64 i64 i64)
    call 37
    local.get 0
    local.get 1
    i64.eq
    if  ;; label = @1
      i64.const 5031766152489992192
      local.get 2
      i64.eq
      if  ;; label = @2
        local.get 0
        local.get 1
        call 77
      else
        i64.const 8516769789752901632
        local.get 2
        i64.eq
        if  ;; label = @3
          local.get 0
          local.get 1
          call 78
        else
          i64.const -4993669930013425664
          local.get 2
          i64.eq
          if  ;; label = @4
            local.get 0
            local.get 1
            call 81
          else
            i64.const -3617168760277827584
            local.get 2
            i64.eq
            if  ;; label = @5
              local.get 0
              local.get 1
              call 82
            else
              i64.const -6533262907872903168
              local.get 2
              i64.eq
              if  ;; label = @6
                local.get 0
                local.get 1
                call 83
              else
                i64.const 4929617502180212736
                local.get 2
                i64.eq
                if  ;; label = @7
                  local.get 0
                  local.get 1
                  call 84
                else
                  local.get 0
                  i64.const 6138663577826885632
                  i64.ne
                  if  ;; label = @8
                    i32.const 0
                    i64.const 8000000000000000000
                    call 34
                  end
                end
              end
            end
          end
        end
      end
    else
      i64.const 6138663577826885632
      local.get 1
      i64.eq
      if  ;; label = @2
        i64.const -6569208335818555392
        local.get 2
        i64.eq
        if  ;; label = @3
          i32.const 0
          i64.const 8000000000000000001
          call 34
        end
      end
    end
    i32.const 0
    call 55)
  (func (;39;) (type 20) (param i32) (result i32)
    (local i32 i32 i32)
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            local.get 0
            i32.eqz
            br_if 0 (;@4;)
            i32.const 0
            i32.const 0
            i32.load offset=8204
            local.get 0
            i32.const 16
            i32.shr_u
            local.tee 1
            i32.add
            local.tee 2
            i32.store offset=8204
            i32.const 0
            i32.const 0
            i32.load offset=8196
            local.tee 3
            local.get 0
            i32.add
            i32.const 7
            i32.add
            i32.const -8
            i32.and
            local.tee 0
            i32.store offset=8196
            local.get 2
            i32.const 16
            i32.shl
            local.get 0
            i32.le_u
            br_if 1 (;@3;)
            local.get 1
            memory.grow
            i32.const -1
            i32.eq
            br_if 2 (;@2;)
            br 3 (;@1;)
          end
          i32.const 0
          return
        end
        i32.const 0
        local.get 2
        i32.const 1
        i32.add
        i32.store offset=8204
        local.get 1
        i32.const 1
        i32.add
        memory.grow
        i32.const -1
        i32.ne
        br_if 1 (;@1;)
      end
      i32.const 0
      i32.const 8220
      call 1
      local.get 3
      return
    end
    local.get 3)
  (func (;40;) (type 18) (param i32))
  (func (;41;) (type 0)
    (local i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 0
    i32.const 0
    i32.store offset=12
    i32.const 0
    local.get 0
    i32.load offset=12
    i32.load
    i32.const 7
    i32.add
    i32.const -8
    i32.and
    local.tee 0
    i32.store offset=8196
    i32.const 0
    local.get 0
    i32.store offset=8192
    i32.const 0
    memory.size
    i32.store offset=8204)
  (func (;42;) (type 10) (result i32)
    i32.const 8208)
  (func (;43;) (type 9) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32)
    i32.const 0
    local.set 2
    block  ;; label = @1
      block  ;; label = @2
        i32.const 0
        local.get 0
        i32.sub
        local.tee 3
        local.get 0
        i32.and
        local.get 0
        i32.ne
        br_if 0 (;@2;)
        local.get 0
        i32.const 16
        i32.gt_u
        br_if 1 (;@1;)
        local.get 1
        call 39
        return
      end
      call 42
      i32.const 22
      i32.store
      i32.const 0
      return
    end
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 0
          i32.const -1
          i32.add
          local.tee 4
          local.get 1
          i32.add
          call 39
          local.tee 0
          i32.eqz
          br_if 0 (;@3;)
          local.get 0
          local.get 4
          local.get 0
          i32.add
          local.get 3
          i32.and
          local.tee 2
          i32.eq
          br_if 1 (;@2;)
          local.get 0
          i32.const -4
          i32.add
          local.tee 3
          i32.load
          local.tee 4
          i32.const 7
          i32.and
          local.tee 1
          i32.eqz
          br_if 2 (;@1;)
          local.get 0
          local.get 4
          i32.const -8
          i32.and
          i32.add
          local.tee 4
          i32.const -8
          i32.add
          local.tee 5
          i32.load
          local.set 6
          local.get 3
          local.get 1
          local.get 2
          local.get 0
          i32.sub
          local.tee 7
          i32.or
          i32.store
          local.get 2
          i32.const -4
          i32.add
          local.get 4
          local.get 2
          i32.sub
          local.tee 3
          local.get 1
          i32.or
          i32.store
          local.get 2
          i32.const -8
          i32.add
          local.get 6
          i32.const 7
          i32.and
          local.tee 1
          local.get 7
          i32.or
          i32.store
          local.get 5
          local.get 1
          local.get 3
          i32.or
          i32.store
          local.get 0
          call 40
        end
        local.get 2
        return
      end
      local.get 0
      return
    end
    local.get 2
    i32.const -8
    i32.add
    local.get 0
    i32.const -8
    i32.add
    i32.load
    local.get 2
    local.get 0
    i32.sub
    local.tee 0
    i32.add
    i32.store
    local.get 2
    i32.const -4
    i32.add
    local.get 3
    i32.load
    local.get 0
    i32.sub
    i32.store
    local.get 2)
  (func (;44;) (type 5) (param i32 i32 i32) (result i32)
    (local i32)
    i32.const 22
    local.set 3
    block  ;; label = @1
      block  ;; label = @2
        local.get 1
        i32.const 4
        i32.lt_u
        br_if 0 (;@2;)
        local.get 1
        local.get 2
        call 43
        local.tee 1
        i32.eqz
        br_if 1 (;@1;)
        local.get 0
        local.get 1
        i32.store
        i32.const 0
        local.set 3
      end
      local.get 3
      return
    end
    call 42
    i32.load)
  (func (;45;) (type 20) (param i32) (result i32)
    (local i32 i32)
    block  ;; label = @1
      local.get 0
      i32.const 1
      local.get 0
      select
      local.tee 1
      call 39
      local.tee 0
      br_if 0 (;@1;)
      loop  ;; label = @2
        i32.const 0
        local.set 0
        i32.const 0
        i32.load offset=8216
        local.tee 2
        i32.eqz
        br_if 1 (;@1;)
        local.get 2
        call_indirect (type 0)
        local.get 1
        call 39
        local.tee 0
        i32.eqz
        br_if 0 (;@2;)
      end
    end
    local.get 0)
  (func (;46;) (type 20) (param i32) (result i32)
    local.get 0
    call 45)
  (func (;47;) (type 18) (param i32)
    block  ;; label = @1
      local.get 0
      i32.eqz
      br_if 0 (;@1;)
      local.get 0
      call 40
    end)
  (func (;48;) (type 18) (param i32)
    local.get 0
    call 47)
  (func (;49;) (type 9) (param i32 i32) (result i32)
    (local i32 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    block  ;; label = @1
      local.get 2
      i32.const 12
      i32.add
      local.get 1
      i32.const 4
      local.get 1
      i32.const 4
      i32.gt_u
      select
      local.tee 1
      local.get 0
      i32.const 1
      local.get 0
      select
      local.tee 3
      call 44
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        loop  ;; label = @3
          i32.const 0
          i32.load offset=8216
          local.tee 0
          i32.eqz
          br_if 1 (;@2;)
          local.get 0
          call_indirect (type 0)
          local.get 2
          i32.const 12
          i32.add
          local.get 1
          local.get 3
          call 44
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      local.get 2
      i32.const 0
      i32.store offset=12
    end
    local.get 2
    i32.load offset=12
    local.set 0
    local.get 2
    i32.const 16
    i32.add
    global.set 0
    local.get 0)
  (func (;50;) (type 9) (param i32 i32) (result i32)
    local.get 0
    local.get 1
    call 49)
  (func (;51;) (type 2) (param i32 i32)
    block  ;; label = @1
      local.get 0
      i32.eqz
      br_if 0 (;@1;)
      local.get 0
      call 40
    end)
  (func (;52;) (type 2) (param i32 i32)
    local.get 0
    local.get 1
    call 51)
  (func (;53;) (type 18) (param i32)
    call 4
    unreachable)
  (func (;54;) (type 2) (param i32 i32)
    (local i32 i32 i32 i32 i32 i32 i32)
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            local.get 1
            i32.const -16
            i32.ge_u
            br_if 0 (;@4;)
            block  ;; label = @5
              block  ;; label = @6
                local.get 0
                i32.load8_u
                local.tee 2
                i32.const 1
                i32.and
                br_if 0 (;@6;)
                local.get 2
                i32.const 1
                i32.shr_u
                local.set 3
                i32.const 10
                local.set 4
                br 1 (;@5;)
              end
              local.get 0
              i32.load
              local.tee 2
              i32.const -2
              i32.and
              i32.const -1
              i32.add
              local.set 4
              local.get 0
              i32.load offset=4
              local.set 3
            end
            i32.const 10
            local.set 5
            block  ;; label = @5
              local.get 3
              local.get 1
              local.get 3
              local.get 1
              i32.gt_u
              select
              local.tee 1
              i32.const 11
              i32.lt_u
              br_if 0 (;@5;)
              local.get 1
              i32.const 16
              i32.add
              i32.const -16
              i32.and
              i32.const -1
              i32.add
              local.set 5
            end
            block  ;; label = @5
              block  ;; label = @6
                block  ;; label = @7
                  local.get 5
                  local.get 4
                  i32.eq
                  br_if 0 (;@7;)
                  block  ;; label = @8
                    local.get 5
                    i32.const 10
                    i32.ne
                    br_if 0 (;@8;)
                    i32.const 1
                    local.set 6
                    local.get 0
                    i32.const 1
                    i32.add
                    local.set 1
                    local.get 0
                    i32.load offset=8
                    local.set 4
                    i32.const 0
                    local.set 7
                    i32.const 1
                    local.set 8
                    local.get 2
                    i32.const 1
                    i32.and
                    br_if 3 (;@5;)
                    br 5 (;@3;)
                  end
                  local.get 5
                  i32.const 1
                  i32.add
                  call 45
                  local.set 1
                  local.get 5
                  local.get 4
                  i32.gt_u
                  br_if 1 (;@6;)
                  local.get 1
                  br_if 1 (;@6;)
                end
                return
              end
              block  ;; label = @6
                local.get 0
                i32.load8_u
                local.tee 2
                i32.const 1
                i32.and
                br_if 0 (;@6;)
                i32.const 1
                local.set 7
                local.get 0
                i32.const 1
                i32.add
                local.set 4
                i32.const 0
                local.set 6
                i32.const 1
                local.set 8
                local.get 2
                i32.const 1
                i32.and
                i32.eqz
                br_if 3 (;@3;)
                br 1 (;@5;)
              end
              local.get 0
              i32.load offset=8
              local.set 4
              i32.const 1
              local.set 6
              i32.const 1
              local.set 7
              i32.const 1
              local.set 8
              local.get 2
              i32.const 1
              i32.and
              i32.eqz
              br_if 2 (;@3;)
            end
            local.get 0
            i32.load offset=4
            i32.const 1
            i32.add
            local.tee 2
            i32.eqz
            br_if 3 (;@1;)
            br 2 (;@2;)
          end
          call 4
          unreachable
        end
        local.get 2
        i32.const 254
        i32.and
        local.get 8
        i32.shr_u
        i32.const 1
        i32.add
        local.tee 2
        i32.eqz
        br_if 1 (;@1;)
      end
      local.get 1
      local.get 4
      local.get 2
      call 8
      drop
    end
    block  ;; label = @1
      local.get 6
      i32.eqz
      br_if 0 (;@1;)
      local.get 4
      call 47
    end
    block  ;; label = @1
      local.get 7
      i32.eqz
      br_if 0 (;@1;)
      local.get 0
      local.get 3
      i32.store offset=4
      local.get 0
      local.get 1
      i32.store offset=8
      local.get 0
      local.get 5
      i32.const 1
      i32.add
      i32.const 1
      i32.or
      i32.store
      return
    end
    local.get 0
    local.get 3
    i32.const 1
    i32.shl
    i32.store8)
  (func (;55;) (type 18) (param i32))
  (func (;56;) (type 18) (param i32)
    call 4
    unreachable)
  (func (;57;) (type 21) (param i32 i32 i32)
    (local i32 i32 i64 i64 i64 i32 i32 i64)
    global.get 0
    i32.const 128
    i32.sub
    local.tee 3
    global.set 0
    local.get 0
    i64.load
    call 0
    i32.const 0
    local.set 4
    local.get 2
    i64.load offset=8
    i64.const 8
    i64.shr_u
    local.tee 5
    local.set 6
    block  ;; label = @1
      block  ;; label = @2
        loop  ;; label = @3
          local.get 6
          i32.wrap_i64
          i32.const 24
          i32.shl
          i32.const -1073741825
          i32.add
          i32.const 452984830
          i32.gt_u
          br_if 1 (;@2;)
          local.get 6
          i64.const 8
          i64.shr_u
          local.set 7
          block  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.eq
            br_if 0 (;@4;)
            local.get 7
            local.set 6
            local.get 4
            local.tee 8
            i32.const 1
            i32.add
            local.set 4
            local.get 8
            i32.const 6
            i32.lt_s
            br_if 1 (;@3;)
            br 3 (;@1;)
          end
          local.get 7
          local.set 6
          loop  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.ne
            br_if 2 (;@2;)
            local.get 6
            i64.const 8
            i64.shr_u
            local.set 6
            local.get 4
            i32.const 6
            i32.lt_s
            local.set 8
            local.get 4
            i32.const 1
            i32.add
            local.tee 9
            local.set 4
            local.get 8
            br_if 0 (;@4;)
          end
          local.get 9
          i32.const 1
          i32.add
          local.set 4
          local.get 9
          i32.const 6
          i32.lt_s
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      i32.const 0
      i32.const 8245
      call 1
    end
    block  ;; label = @1
      block  ;; label = @2
        local.get 2
        i64.load
        local.tee 10
        i64.const 4611686018427387903
        i64.add
        i64.const 9223372036854775806
        i64.gt_u
        br_if 0 (;@2;)
        local.get 2
        i32.const 8
        i32.add
        i64.load
        i64.const 8
        i64.shr_u
        local.set 6
        i32.const 0
        local.set 4
        loop  ;; label = @3
          local.get 6
          i32.wrap_i64
          i32.const 24
          i32.shl
          i32.const -1073741825
          i32.add
          i32.const 452984830
          i32.gt_u
          br_if 1 (;@2;)
          local.get 6
          i64.const 8
          i64.shr_u
          local.set 7
          block  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.eq
            br_if 0 (;@4;)
            local.get 7
            local.set 6
            local.get 4
            local.tee 8
            i32.const 1
            i32.add
            local.set 4
            local.get 8
            i32.const 6
            i32.lt_s
            br_if 1 (;@3;)
            br 3 (;@1;)
          end
          local.get 7
          local.set 6
          loop  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.ne
            br_if 2 (;@2;)
            local.get 6
            i64.const 8
            i64.shr_u
            local.set 6
            local.get 4
            i32.const 6
            i32.lt_s
            local.set 8
            local.get 4
            i32.const 1
            i32.add
            local.tee 9
            local.set 4
            local.get 8
            br_if 0 (;@4;)
          end
          local.get 9
          i32.const 1
          i32.add
          local.set 4
          local.get 9
          i32.const 6
          i32.lt_s
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      i32.const 0
      i32.const 8265
      call 1
      local.get 2
      i64.load
      local.set 10
    end
    block  ;; label = @1
      local.get 10
      i64.const 0
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8280
      call 1
    end
    local.get 3
    i32.const 40
    i32.add
    i32.const 0
    i32.store
    local.get 3
    i64.const -1
    i64.store offset=24
    local.get 3
    i64.const 0
    i64.store offset=32
    local.get 3
    local.get 0
    i64.load
    local.tee 6
    i64.store offset=8
    local.get 3
    local.get 5
    i64.store offset=16
    block  ;; label = @1
      local.get 6
      local.get 5
      i64.const -4157508551318700032
      local.get 5
      call 2
      local.tee 4
      i32.const 0
      i32.lt_s
      br_if 0 (;@1;)
      block  ;; label = @2
        local.get 3
        i32.const 8
        i32.add
        local.get 4
        call 58
        i32.load offset=40
        local.get 3
        i32.const 8
        i32.add
        i32.eq
        br_if 0 (;@2;)
        i32.const 0
        i32.const 8959
        call 1
      end
      i32.const 0
      i32.const 8308
      call 1
    end
    local.get 0
    i64.load
    local.set 7
    block  ;; label = @1
      call 3
      local.get 3
      i64.load offset=8
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9033
      call 1
    end
    i32.const 56
    call 45
    local.tee 4
    i64.const 0
    i64.store offset=16
    local.get 4
    i64.const 0
    i64.store
    local.get 4
    i64.const 0
    i64.store offset=24
    local.get 4
    local.get 3
    i32.const 8
    i32.add
    i32.store offset=40
    local.get 4
    local.get 2
    i32.const 8
    i32.add
    i64.load
    local.tee 6
    i64.store offset=8
    local.get 4
    local.get 2
    i64.load
    i64.store offset=16
    local.get 4
    local.get 6
    i64.store offset=24
    local.get 4
    local.get 1
    i64.load
    i64.store offset=32
    local.get 3
    local.get 3
    i32.const 48
    i32.add
    i32.const 40
    i32.add
    i32.store offset=96
    local.get 3
    local.get 3
    i32.const 48
    i32.add
    i32.store offset=92
    local.get 3
    local.get 3
    i32.const 48
    i32.add
    i32.store offset=88
    local.get 3
    local.get 3
    i32.const 88
    i32.add
    i32.store offset=104
    local.get 3
    local.get 4
    i32.const 16
    i32.add
    i32.store offset=116
    local.get 3
    local.get 4
    i32.store offset=112
    local.get 3
    local.get 4
    i32.const 32
    i32.add
    i32.store offset=120
    local.get 3
    i32.const 112
    i32.add
    local.get 3
    i32.const 104
    i32.add
    call 59
    local.get 4
    local.get 3
    i32.const 8
    i32.add
    i32.const 8
    i32.add
    i64.load
    i64.const -4157508551318700032
    local.get 7
    local.get 4
    i64.load offset=8
    i64.const 8
    i64.shr_u
    local.tee 6
    local.get 3
    i32.const 48
    i32.add
    i32.const 40
    call 6
    local.tee 9
    i32.store offset=44
    block  ;; label = @1
      local.get 6
      local.get 3
      i32.const 8
      i32.add
      i32.const 16
      i32.add
      local.tee 8
      i64.load
      i64.lt_u
      br_if 0 (;@1;)
      local.get 8
      local.get 6
      i64.const 1
      i64.add
      i64.store
    end
    local.get 3
    local.get 4
    i32.store offset=112
    local.get 3
    local.get 4
    i32.const 8
    i32.add
    i64.load
    i64.const 8
    i64.shr_u
    local.tee 6
    i64.store offset=48
    local.get 3
    local.get 9
    i32.store offset=88
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 3
          i32.const 36
          i32.add
          local.tee 2
          i32.load
          local.tee 8
          local.get 3
          i32.const 8
          i32.add
          i32.const 32
          i32.add
          i32.load
          i32.ge_u
          br_if 0 (;@3;)
          local.get 8
          local.get 6
          i64.store offset=8
          local.get 8
          local.get 9
          i32.store offset=16
          local.get 3
          i32.const 0
          i32.store offset=112
          local.get 8
          local.get 4
          i32.store
          local.get 2
          local.get 8
          i32.const 24
          i32.add
          i32.store
          local.get 3
          i32.load offset=112
          local.set 4
          local.get 3
          i32.const 0
          i32.store offset=112
          local.get 4
          br_if 1 (;@2;)
          br 2 (;@1;)
        end
        local.get 3
        i32.const 32
        i32.add
        local.get 3
        i32.const 112
        i32.add
        local.get 3
        i32.const 48
        i32.add
        local.get 3
        i32.const 88
        i32.add
        call 60
        local.get 3
        i32.load offset=112
        local.set 4
        local.get 3
        i32.const 0
        i32.store offset=112
        local.get 4
        i32.eqz
        br_if 1 (;@1;)
      end
      local.get 4
      call 47
    end
    block  ;; label = @1
      local.get 3
      i32.load offset=32
      local.tee 9
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        block  ;; label = @3
          local.get 3
          i32.const 36
          i32.add
          local.tee 2
          i32.load
          local.tee 4
          local.get 9
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 4
            i32.const -24
            i32.add
            local.tee 4
            i32.load
            local.set 8
            local.get 4
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 8
              i32.eqz
              br_if 0 (;@5;)
              local.get 8
              call 47
            end
            local.get 9
            local.get 4
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 3
          i32.const 32
          i32.add
          i32.load
          local.set 4
          br 1 (;@2;)
        end
        local.get 9
        local.set 4
      end
      local.get 2
      local.get 9
      i32.store
      local.get 4
      call 47
    end
    local.get 3
    i32.const 128
    i32.add
    global.set 0)
  (func (;58;) (type 9) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i64 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      local.get 0
      i32.load offset=24
      local.tee 4
      local.get 0
      i32.const 28
      i32.add
      i32.load
      local.tee 5
      i32.eq
      br_if 0 (;@1;)
      block  ;; label = @2
        loop  ;; label = @3
          local.get 5
          i32.const -8
          i32.add
          i32.load
          local.get 1
          i32.eq
          br_if 1 (;@2;)
          local.get 4
          local.get 5
          i32.const -24
          i32.add
          local.tee 5
          i32.ne
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      local.get 4
      local.get 5
      i32.eq
      br_if 0 (;@1;)
      local.get 5
      i32.const -24
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.const 48
      i32.add
      global.set 0
      local.get 5
      return
    end
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 1
          i32.const 0
          i32.const 0
          call 35
          local.tee 5
          i32.const -1
          i32.le_s
          br_if 0 (;@3;)
          local.get 5
          i32.const 513
          i32.ge_u
          br_if 1 (;@2;)
          local.get 2
          local.get 5
          i32.const 15
          i32.add
          i32.const -16
          i32.and
          i32.sub
          local.tee 4
          global.set 0
          i32.const 0
          local.set 6
          br 2 (;@1;)
        end
        i32.const 0
        i32.const 9010
        call 1
      end
      local.get 5
      call 39
      local.set 4
      i32.const 1
      local.set 6
    end
    local.get 1
    local.get 4
    local.get 5
    call 35
    drop
    local.get 3
    local.get 4
    i32.store offset=12
    local.get 3
    local.get 4
    i32.store offset=8
    local.get 3
    local.get 4
    local.get 5
    i32.add
    i32.store offset=16
    i32.const 56
    call 45
    local.tee 5
    i64.const 0
    i64.store offset=8
    local.get 5
    i64.const 0
    i64.store
    local.get 5
    i64.const 0
    i64.store offset=16
    local.get 5
    i64.const 0
    i64.store offset=24
    local.get 5
    i64.const 0
    i64.store offset=32
    local.get 5
    local.get 0
    i32.store offset=40
    local.get 3
    local.get 3
    i32.const 8
    i32.add
    i32.store offset=24
    local.get 3
    local.get 5
    i32.const 16
    i32.add
    i32.store offset=36
    local.get 3
    local.get 5
    i32.store offset=32
    local.get 3
    local.get 5
    i32.const 32
    i32.add
    i32.store offset=40
    local.get 3
    i32.const 32
    i32.add
    local.get 3
    i32.const 24
    i32.add
    call 85
    local.get 5
    local.get 1
    i32.store offset=44
    local.get 3
    local.get 5
    i32.store offset=24
    local.get 3
    local.get 5
    i64.load offset=8
    i64.const 8
    i64.shr_u
    local.tee 7
    i64.store offset=32
    local.get 3
    local.get 1
    i32.store offset=4
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 0
          i32.const 28
          i32.add
          local.tee 8
          i32.load
          local.tee 2
          local.get 0
          i32.const 32
          i32.add
          i32.load
          i32.ge_u
          br_if 0 (;@3;)
          local.get 2
          local.get 7
          i64.store offset=8
          local.get 2
          local.get 1
          i32.store offset=16
          local.get 3
          i32.const 0
          i32.store offset=24
          local.get 2
          local.get 5
          i32.store
          local.get 8
          local.get 2
          i32.const 24
          i32.add
          i32.store
          local.get 6
          br_if 1 (;@2;)
          br 2 (;@1;)
        end
        local.get 0
        i32.const 24
        i32.add
        local.get 3
        i32.const 24
        i32.add
        local.get 3
        i32.const 32
        i32.add
        local.get 3
        i32.const 4
        i32.add
        call 60
        local.get 6
        i32.eqz
        br_if 1 (;@1;)
      end
      local.get 4
      call 40
    end
    local.get 3
    i32.load offset=24
    local.set 1
    local.get 3
    i32.const 0
    i32.store offset=24
    block  ;; label = @1
      local.get 1
      i32.eqz
      br_if 0 (;@1;)
      local.get 1
      call 47
    end
    local.get 3
    i32.const 48
    i32.add
    global.set 0
    local.get 5)
  (func (;59;) (type 2) (param i32 i32)
    (local i32 i32 i32 i32 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 0
    i32.load
    local.set 3
    block  ;; label = @1
      local.get 1
      i32.load
      local.tee 4
      i32.load offset=8
      local.get 4
      i32.load offset=4
      local.tee 5
      i32.sub
      i32.const 7
      i32.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9084
      call 1
      local.get 4
      i32.const 4
      i32.add
      i32.load
      local.set 5
    end
    local.get 5
    local.get 3
    i32.const 8
    call 8
    drop
    local.get 4
    i32.const 4
    i32.add
    local.tee 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    local.tee 6
    i32.store
    local.get 2
    local.get 3
    i64.load offset=8
    i64.store offset=8
    block  ;; label = @1
      local.get 4
      i32.const 8
      i32.add
      i32.load
      local.get 6
      i32.sub
      i32.const 7
      i32.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9084
      call 1
      local.get 5
      i32.load
      local.set 6
    end
    local.get 6
    local.get 2
    i32.const 8
    i32.add
    i32.const 8
    call 8
    drop
    local.get 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    i32.store
    local.get 0
    i32.load offset=4
    local.set 3
    block  ;; label = @1
      local.get 1
      i32.load
      local.tee 4
      i32.load offset=8
      local.get 4
      i32.load offset=4
      local.tee 5
      i32.sub
      i32.const 7
      i32.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9084
      call 1
      local.get 4
      i32.const 4
      i32.add
      i32.load
      local.set 5
    end
    local.get 5
    local.get 3
    i32.const 8
    call 8
    drop
    local.get 4
    i32.const 4
    i32.add
    local.tee 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    local.tee 6
    i32.store
    local.get 2
    local.get 3
    i64.load offset=8
    i64.store offset=8
    block  ;; label = @1
      local.get 4
      i32.const 8
      i32.add
      i32.load
      local.get 6
      i32.sub
      i32.const 7
      i32.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9084
      call 1
      local.get 5
      i32.load
      local.set 6
    end
    local.get 6
    local.get 2
    i32.const 8
    i32.add
    i32.const 8
    call 8
    drop
    local.get 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    i32.store
    local.get 0
    i32.load offset=8
    local.set 0
    block  ;; label = @1
      local.get 1
      i32.load
      local.tee 4
      i32.load offset=8
      local.get 4
      i32.load offset=4
      local.tee 5
      i32.sub
      i32.const 7
      i32.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9084
      call 1
      local.get 4
      i32.const 4
      i32.add
      i32.load
      local.set 5
    end
    local.get 5
    local.get 0
    i32.const 8
    call 8
    drop
    local.get 4
    i32.const 4
    i32.add
    local.tee 4
    local.get 4
    i32.load
    i32.const 8
    i32.add
    i32.store
    local.get 2
    i32.const 16
    i32.add
    global.set 0)
  (func (;60;) (type 22) (param i32 i32 i32 i32)
    (local i32 i32 i32 i32 i32)
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        i32.load offset=4
        local.get 0
        i32.load
        local.tee 4
        i32.sub
        i32.const 24
        i32.div_s
        local.tee 5
        i32.const 1
        i32.add
        local.tee 6
        i32.const 178956971
        i32.ge_u
        br_if 0 (;@2;)
        i32.const 178956970
        local.set 7
        block  ;; label = @3
          block  ;; label = @4
            local.get 0
            i32.load offset=8
            local.get 4
            i32.sub
            i32.const 24
            i32.div_s
            local.tee 4
            i32.const 89478484
            i32.gt_u
            br_if 0 (;@4;)
            local.get 6
            local.get 4
            i32.const 1
            i32.shl
            local.tee 7
            local.get 7
            local.get 6
            i32.lt_u
            select
            local.tee 7
            i32.eqz
            br_if 1 (;@3;)
          end
          local.get 7
          i32.const 24
          i32.mul
          call 45
          local.set 4
          br 2 (;@1;)
        end
        i32.const 0
        local.set 7
        i32.const 0
        local.set 4
        br 1 (;@1;)
      end
      local.get 0
      call 56
      unreachable
    end
    local.get 1
    i32.load
    local.set 6
    local.get 1
    i32.const 0
    i32.store
    local.get 4
    local.get 5
    i32.const 24
    i32.mul
    local.tee 8
    i32.add
    local.tee 1
    local.get 6
    i32.store
    local.get 1
    local.get 2
    i64.load
    i64.store offset=8
    local.get 1
    local.get 3
    i32.load
    i32.store offset=16
    local.get 4
    local.get 7
    i32.const 24
    i32.mul
    i32.add
    local.set 5
    local.get 1
    i32.const 24
    i32.add
    local.set 6
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        i32.const 4
        i32.add
        i32.load
        local.tee 2
        local.get 0
        i32.load
        local.tee 7
        i32.eq
        br_if 0 (;@2;)
        local.get 4
        local.get 8
        i32.add
        i32.const -24
        i32.add
        local.set 1
        loop  ;; label = @3
          local.get 2
          i32.const -24
          i32.add
          local.tee 4
          i32.load
          local.set 3
          local.get 4
          i32.const 0
          i32.store
          local.get 1
          local.get 3
          i32.store
          local.get 1
          i32.const 16
          i32.add
          local.get 2
          i32.const -8
          i32.add
          i32.load
          i32.store
          local.get 1
          i32.const 8
          i32.add
          local.get 2
          i32.const -16
          i32.add
          i64.load
          i64.store
          local.get 1
          i32.const -24
          i32.add
          local.set 1
          local.get 4
          local.set 2
          local.get 7
          local.get 4
          i32.ne
          br_if 0 (;@3;)
        end
        local.get 1
        i32.const 24
        i32.add
        local.set 1
        local.get 0
        i32.const 4
        i32.add
        i32.load
        local.set 7
        local.get 0
        i32.load
        local.set 2
        br 1 (;@1;)
      end
      local.get 7
      local.set 2
    end
    local.get 0
    local.get 1
    i32.store
    local.get 0
    i32.const 4
    i32.add
    local.get 6
    i32.store
    local.get 0
    i32.const 8
    i32.add
    local.get 5
    i32.store
    block  ;; label = @1
      local.get 7
      local.get 2
      i32.eq
      br_if 0 (;@1;)
      loop  ;; label = @2
        local.get 7
        i32.const -24
        i32.add
        local.tee 7
        i32.load
        local.set 1
        local.get 7
        i32.const 0
        i32.store
        block  ;; label = @3
          local.get 1
          i32.eqz
          br_if 0 (;@3;)
          local.get 1
          call 47
        end
        local.get 2
        local.get 7
        i32.ne
        br_if 0 (;@2;)
      end
    end
    block  ;; label = @1
      local.get 2
      i32.eqz
      br_if 0 (;@1;)
      local.get 2
      call 47
    end)
  (func (;61;) (type 22) (param i32 i32 i32 i32)
    (local i32 i32 i64 i64 i64 i32 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 4
    global.set 0
    i32.const 0
    local.set 5
    local.get 2
    i64.load offset=8
    i64.const 8
    i64.shr_u
    local.tee 6
    local.set 7
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          loop  ;; label = @4
            local.get 7
            i32.wrap_i64
            i32.const 24
            i32.shl
            i32.const -1073741825
            i32.add
            i32.const 452984830
            i32.gt_u
            br_if 1 (;@3;)
            block  ;; label = @5
              local.get 7
              i64.const 8
              i64.shr_u
              local.set 8
              block  ;; label = @6
                local.get 7
                i64.const 65280
                i64.and
                i64.const 0
                i64.eq
                br_if 0 (;@6;)
                local.get 8
                local.set 7
                local.get 5
                local.tee 9
                i32.const 1
                i32.add
                local.set 5
                local.get 9
                i32.const 6
                i32.lt_s
                br_if 2 (;@4;)
                br 1 (;@5;)
              end
              local.get 8
              local.set 7
              loop  ;; label = @6
                local.get 7
                i64.const 65280
                i64.and
                i64.const 0
                i64.ne
                br_if 3 (;@3;)
                local.get 7
                i64.const 8
                i64.shr_u
                local.set 7
                local.get 5
                i32.const 6
                i32.lt_s
                local.set 9
                local.get 5
                i32.const 1
                i32.add
                local.tee 10
                local.set 5
                local.get 9
                br_if 0 (;@6;)
              end
              local.get 10
              i32.const 1
              i32.add
              local.set 5
              local.get 10
              i32.const 6
              i32.lt_s
              br_if 1 (;@4;)
            end
          end
          local.get 3
          i32.load8_u
          i32.const 1
          i32.and
          i32.eqz
          br_if 2 (;@1;)
          br 1 (;@2;)
        end
        i32.const 0
        i32.const 8245
        call 1
        local.get 3
        i32.load8_u
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
      end
      local.get 3
      i32.load offset=4
      i32.const 257
      i32.lt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8341
      call 1
    end
    i32.const 0
    local.set 3
    local.get 4
    i32.const 40
    i32.add
    i32.const 0
    i32.store
    local.get 4
    i64.const -1
    i64.store offset=24
    local.get 4
    i64.const 0
    i64.store offset=32
    local.get 4
    local.get 0
    i64.load
    local.tee 7
    i64.store offset=8
    local.get 4
    local.get 6
    i64.store offset=16
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 7
          local.get 6
          i64.const -4157508551318700032
          local.get 6
          call 2
          local.tee 5
          i32.const 0
          i32.lt_s
          br_if 0 (;@3;)
          block  ;; label = @4
            local.get 4
            i32.const 8
            i32.add
            local.get 5
            call 58
            local.tee 3
            i32.load offset=40
            local.get 4
            i32.const 8
            i32.add
            i32.eq
            br_if 0 (;@4;)
            i32.const 0
            i32.const 8959
            call 1
          end
          local.get 1
          i64.load
          local.tee 7
          local.get 3
          i64.load offset=32
          i64.eq
          br_if 2 (;@1;)
          br 1 (;@2;)
        end
        i32.const 0
        i32.const 8370
        call 1
        local.get 1
        i64.load
        local.tee 7
        i32.const 0
        i64.load offset=32
        i64.eq
        br_if 1 (;@1;)
      end
      i32.const 0
      i32.const 8430
      call 1
      local.get 3
      i64.load offset=32
      local.set 7
    end
    local.get 7
    call 0
    block  ;; label = @1
      block  ;; label = @2
        local.get 2
        i64.load
        local.tee 6
        i64.const 4611686018427387903
        i64.add
        i64.const 9223372036854775806
        i64.gt_u
        br_if 0 (;@2;)
        local.get 2
        i32.const 8
        i32.add
        i64.load
        i64.const 8
        i64.shr_u
        local.set 7
        i32.const 0
        local.set 5
        loop  ;; label = @3
          local.get 7
          i32.wrap_i64
          i32.const 24
          i32.shl
          i32.const -1073741825
          i32.add
          i32.const 452984830
          i32.gt_u
          br_if 1 (;@2;)
          local.get 7
          i64.const 8
          i64.shr_u
          local.set 8
          block  ;; label = @4
            local.get 7
            i64.const 65280
            i64.and
            i64.const 0
            i64.eq
            br_if 0 (;@4;)
            local.get 8
            local.set 7
            local.get 5
            local.tee 9
            i32.const 1
            i32.add
            local.set 5
            local.get 9
            i32.const 6
            i32.lt_s
            br_if 1 (;@3;)
            br 3 (;@1;)
          end
          local.get 8
          local.set 7
          loop  ;; label = @4
            local.get 7
            i64.const 65280
            i64.and
            i64.const 0
            i64.ne
            br_if 2 (;@2;)
            local.get 7
            i64.const 8
            i64.shr_u
            local.set 7
            local.get 5
            i32.const 6
            i32.lt_s
            local.set 9
            local.get 5
            i32.const 1
            i32.add
            local.tee 10
            local.set 5
            local.get 9
            br_if 0 (;@4;)
          end
          local.get 10
          i32.const 1
          i32.add
          local.set 5
          local.get 10
          i32.const 6
          i32.lt_s
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      i32.const 0
      i32.const 8474
      call 1
      local.get 2
      i64.load
      local.set 6
    end
    block  ;; label = @1
      local.get 6
      i64.const 0
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8491
      call 1
    end
    block  ;; label = @1
      local.get 2
      i32.const 8
      i32.add
      i64.load
      local.get 3
      i64.load offset=8
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8520
      call 1
    end
    local.get 3
    i32.const 32
    i32.add
    local.set 5
    block  ;; label = @1
      local.get 2
      i64.load
      local.get 3
      i64.load offset=16
      local.get 3
      i64.load
      i64.sub
      i64.le_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8546
      call 1
    end
    local.get 4
    local.get 2
    i32.store
    local.get 4
    i32.const 8
    i32.add
    local.get 3
    local.get 4
    call 62
    local.get 0
    local.get 5
    local.get 2
    local.get 5
    call 63
    block  ;; label = @1
      local.get 4
      i32.load offset=32
      local.tee 10
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        block  ;; label = @3
          local.get 4
          i32.const 36
          i32.add
          local.tee 2
          i32.load
          local.tee 5
          local.get 10
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 5
            i32.const -24
            i32.add
            local.tee 5
            i32.load
            local.set 9
            local.get 5
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 9
              i32.eqz
              br_if 0 (;@5;)
              local.get 9
              call 47
            end
            local.get 10
            local.get 5
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 4
          i32.const 32
          i32.add
          i32.load
          local.set 5
          br 1 (;@2;)
        end
        local.get 10
        local.set 5
      end
      local.get 2
      local.get 10
      i32.store
      local.get 5
      call 47
    end
    local.get 4
    i32.const 48
    i32.add
    global.set 0)
  (func (;62;) (type 21) (param i32 i32 i32)
    (local i32 i32 i64 i64)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 3
    local.set 4
    local.get 3
    global.set 0
    block  ;; label = @1
      local.get 1
      i32.load offset=40
      local.get 0
      i32.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9090
      call 1
    end
    block  ;; label = @1
      call 3
      local.get 0
      i64.load
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9136
      call 1
    end
    block  ;; label = @1
      local.get 2
      i32.load
      local.tee 2
      i64.load offset=8
      local.get 1
      i64.load offset=8
      local.tee 5
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9246
      call 1
    end
    local.get 1
    local.get 1
    i64.load
    local.get 2
    i64.load
    i64.add
    local.tee 6
    i64.store
    block  ;; label = @1
      local.get 6
      i64.const -4611686018427387904
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9289
      call 1
      local.get 1
      i64.load
      local.set 6
    end
    local.get 5
    i64.const 8
    i64.shr_u
    local.set 5
    block  ;; label = @1
      local.get 6
      i64.const 4611686018427387904
      i64.lt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9308
      call 1
    end
    block  ;; label = @1
      local.get 5
      local.get 1
      i32.const 8
      i32.add
      i64.load
      i64.const 8
      i64.shr_u
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9187
      call 1
    end
    local.get 3
    local.tee 2
    i32.const -48
    i32.add
    local.tee 3
    global.set 0
    local.get 4
    local.get 3
    i32.store offset=12
    local.get 4
    local.get 3
    i32.store offset=8
    local.get 4
    local.get 2
    i32.const -8
    i32.add
    i32.store offset=16
    local.get 4
    local.get 4
    i32.const 8
    i32.add
    i32.store offset=24
    local.get 4
    local.get 1
    i32.store offset=32
    local.get 4
    local.get 1
    i32.const 16
    i32.add
    i32.store offset=36
    local.get 4
    local.get 1
    i32.const 32
    i32.add
    i32.store offset=40
    local.get 4
    i32.const 32
    i32.add
    local.get 4
    i32.const 24
    i32.add
    call 59
    local.get 1
    i32.load offset=44
    i64.const 0
    local.get 3
    i32.const 40
    call 7
    block  ;; label = @1
      local.get 5
      local.get 0
      i64.load offset=16
      i64.lt_u
      br_if 0 (;@1;)
      local.get 0
      i32.const 16
      i32.add
      local.get 5
      i64.const 1
      i64.add
      i64.store
    end
    local.get 4
    i32.const 48
    i32.add
    global.set 0)
  (func (;63;) (type 22) (param i32 i32 i32 i32)
    (local i32 i64 i64)
    global.get 0
    i32.const 80
    i32.sub
    local.tee 4
    global.set 0
    local.get 4
    i32.const 32
    i32.add
    i32.const 0
    i32.store
    local.get 4
    i64.const -1
    i64.store offset=16
    local.get 4
    i64.const 0
    i64.store offset=24
    local.get 4
    local.get 0
    i64.load
    local.tee 5
    i64.store
    local.get 4
    local.get 1
    i64.load
    local.tee 6
    i64.store offset=8
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 5
          local.get 6
          i64.const 3607749779137757184
          local.get 2
          i64.load offset=8
          i64.const 8
          i64.shr_u
          call 2
          local.tee 1
          i32.const 0
          i32.lt_s
          br_if 0 (;@3;)
          block  ;; label = @4
            local.get 4
            local.get 1
            call 64
            local.tee 1
            i32.load offset=16
            local.get 4
            i32.eq
            br_if 0 (;@4;)
            i32.const 0
            i32.const 8959
            call 1
          end
          local.get 4
          local.get 2
          i32.store offset=48
          local.get 4
          local.get 1
          local.get 4
          i32.const 48
          i32.add
          call 65
          local.get 4
          i32.load offset=24
          local.tee 0
          br_if 1 (;@2;)
          br 2 (;@1;)
        end
        local.get 3
        i64.load
        local.set 6
        block  ;; label = @3
          call 3
          local.get 4
          i64.load
          i64.eq
          br_if 0 (;@3;)
          i32.const 0
          i32.const 9033
          call 1
        end
        i32.const 32
        call 45
        local.tee 1
        local.get 4
        i32.store offset=16
        local.get 1
        local.get 2
        i32.const 8
        i32.add
        i64.load
        i64.store offset=8
        local.get 1
        local.get 2
        i64.load
        i64.store
        local.get 4
        i32.const 48
        i32.add
        local.get 1
        i32.const 8
        call 8
        drop
        local.get 4
        local.get 1
        i64.load offset=8
        i64.store offset=72
        local.get 4
        i32.const 48
        i32.add
        i32.const 8
        i32.or
        local.get 4
        i32.const 72
        i32.add
        i32.const 8
        call 8
        drop
        local.get 1
        local.get 4
        i32.const 8
        i32.add
        i64.load
        i64.const 3607749779137757184
        local.get 6
        local.get 1
        i64.load offset=8
        i64.const 8
        i64.shr_u
        local.tee 5
        local.get 4
        i32.const 48
        i32.add
        i32.const 16
        call 6
        local.tee 0
        i32.store offset=20
        block  ;; label = @3
          local.get 5
          local.get 4
          i32.const 16
          i32.add
          local.tee 2
          i64.load
          i64.lt_u
          br_if 0 (;@3;)
          local.get 2
          local.get 5
          i64.const 1
          i64.add
          i64.store
        end
        local.get 4
        local.get 1
        i32.store offset=72
        local.get 4
        local.get 1
        i32.const 8
        i32.add
        i64.load
        i64.const 8
        i64.shr_u
        local.tee 5
        i64.store offset=48
        local.get 4
        local.get 0
        i32.store offset=44
        block  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              local.get 4
              i32.const 28
              i32.add
              local.tee 3
              i32.load
              local.tee 2
              local.get 4
              i32.const 32
              i32.add
              i32.load
              i32.ge_u
              br_if 0 (;@5;)
              local.get 2
              local.get 5
              i64.store offset=8
              local.get 2
              local.get 0
              i32.store offset=16
              local.get 4
              i32.const 0
              i32.store offset=72
              local.get 2
              local.get 1
              i32.store
              local.get 3
              local.get 2
              i32.const 24
              i32.add
              i32.store
              local.get 4
              i32.load offset=72
              local.set 1
              local.get 4
              i32.const 0
              i32.store offset=72
              local.get 1
              br_if 1 (;@4;)
              br 2 (;@3;)
            end
            local.get 4
            i32.const 24
            i32.add
            local.get 4
            i32.const 72
            i32.add
            local.get 4
            i32.const 48
            i32.add
            local.get 4
            i32.const 44
            i32.add
            call 66
            local.get 4
            i32.load offset=72
            local.set 1
            local.get 4
            i32.const 0
            i32.store offset=72
            local.get 1
            i32.eqz
            br_if 1 (;@3;)
          end
          local.get 1
          call 47
        end
        local.get 4
        i32.load offset=24
        local.tee 0
        i32.eqz
        br_if 1 (;@1;)
      end
      block  ;; label = @2
        block  ;; label = @3
          local.get 4
          i32.const 28
          i32.add
          local.tee 3
          i32.load
          local.tee 1
          local.get 0
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 1
            i32.const -24
            i32.add
            local.tee 1
            i32.load
            local.set 2
            local.get 1
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 2
              i32.eqz
              br_if 0 (;@5;)
              local.get 2
              call 47
            end
            local.get 0
            local.get 1
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 4
          i32.const 24
          i32.add
          i32.load
          local.set 1
          br 1 (;@2;)
        end
        local.get 0
        local.set 1
      end
      local.get 3
      local.get 0
      i32.store
      local.get 1
      call 47
    end
    local.get 4
    i32.const 80
    i32.add
    global.set 0)
  (func (;64;) (type 9) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32 i64)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      local.get 0
      i32.load offset=24
      local.tee 4
      local.get 0
      i32.const 28
      i32.add
      i32.load
      local.tee 5
      i32.eq
      br_if 0 (;@1;)
      block  ;; label = @2
        loop  ;; label = @3
          local.get 5
          i32.const -8
          i32.add
          i32.load
          local.get 1
          i32.eq
          br_if 1 (;@2;)
          local.get 4
          local.get 5
          i32.const -24
          i32.add
          local.tee 5
          i32.ne
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      local.get 4
      local.get 5
      i32.eq
      br_if 0 (;@1;)
      local.get 5
      i32.const -24
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.const 32
      i32.add
      global.set 0
      local.get 5
      return
    end
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 1
          i32.const 0
          i32.const 0
          call 35
          local.tee 4
          i32.const -1
          i32.le_s
          br_if 0 (;@3;)
          local.get 4
          i32.const 513
          i32.ge_u
          br_if 1 (;@2;)
          local.get 2
          local.get 4
          i32.const 15
          i32.add
          i32.const -16
          i32.and
          i32.sub
          local.tee 2
          global.set 0
          i32.const 0
          local.set 6
          br 2 (;@1;)
        end
        i32.const 0
        i32.const 9010
        call 1
      end
      local.get 4
      call 39
      local.set 2
      i32.const 1
      local.set 6
    end
    local.get 1
    local.get 2
    local.get 4
    call 35
    drop
    i32.const 32
    call 45
    local.tee 5
    i64.const 0
    i64.store offset=8
    local.get 5
    i64.const 0
    i64.store
    local.get 5
    local.get 0
    i32.store offset=16
    block  ;; label = @1
      local.get 4
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 5
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    i64.const 0
    i64.store offset=24
    local.get 2
    i32.const 8
    i32.add
    local.set 7
    block  ;; label = @1
      local.get 4
      i32.const -8
      i32.and
      i32.const 8
      i32.ne
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 3
    i32.const 24
    i32.add
    local.get 7
    i32.const 8
    call 8
    drop
    local.get 5
    i32.const 8
    i32.add
    local.get 3
    i64.load offset=24
    local.tee 8
    i64.store
    local.get 5
    local.get 1
    i32.store offset=20
    local.get 3
    local.get 5
    i32.store offset=16
    local.get 3
    local.get 8
    i64.const 8
    i64.shr_u
    local.tee 8
    i64.store offset=24
    local.get 3
    local.get 1
    i32.store offset=12
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 0
          i32.const 28
          i32.add
          local.tee 7
          i32.load
          local.tee 4
          local.get 0
          i32.const 32
          i32.add
          i32.load
          i32.ge_u
          br_if 0 (;@3;)
          local.get 4
          local.get 8
          i64.store offset=8
          local.get 4
          local.get 1
          i32.store offset=16
          local.get 3
          i32.const 0
          i32.store offset=16
          local.get 4
          local.get 5
          i32.store
          local.get 7
          local.get 4
          i32.const 24
          i32.add
          i32.store
          local.get 6
          br_if 1 (;@2;)
          br 2 (;@1;)
        end
        local.get 0
        i32.const 24
        i32.add
        local.get 3
        i32.const 16
        i32.add
        local.get 3
        i32.const 24
        i32.add
        local.get 3
        i32.const 12
        i32.add
        call 66
        local.get 6
        i32.eqz
        br_if 1 (;@1;)
      end
      local.get 2
      call 40
    end
    local.get 3
    i32.load offset=16
    local.set 1
    local.get 3
    i32.const 0
    i32.store offset=16
    block  ;; label = @1
      local.get 1
      i32.eqz
      br_if 0 (;@1;)
      local.get 1
      call 47
    end
    local.get 3
    i32.const 32
    i32.add
    global.set 0
    local.get 5)
  (func (;65;) (type 21) (param i32 i32 i32)
    (local i32 i32 i64 i64 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 3
    local.set 4
    local.get 3
    global.set 0
    block  ;; label = @1
      local.get 1
      i32.load offset=16
      local.get 0
      i32.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9090
      call 1
    end
    block  ;; label = @1
      call 3
      local.get 0
      i64.load
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9136
      call 1
    end
    block  ;; label = @1
      local.get 2
      i32.load
      local.tee 2
      i64.load offset=8
      local.get 1
      i64.load offset=8
      local.tee 5
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9246
      call 1
    end
    local.get 1
    local.get 1
    i64.load
    local.get 2
    i64.load
    i64.add
    local.tee 6
    i64.store
    block  ;; label = @1
      local.get 6
      i64.const -4611686018427387904
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9289
      call 1
      local.get 1
      i64.load
      local.set 6
    end
    local.get 5
    i64.const 8
    i64.shr_u
    local.set 5
    block  ;; label = @1
      local.get 6
      i64.const 4611686018427387904
      i64.lt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9308
      call 1
    end
    block  ;; label = @1
      local.get 5
      local.get 1
      i32.const 8
      i32.add
      local.tee 2
      i64.load
      i64.const 8
      i64.shr_u
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9187
      call 1
    end
    local.get 3
    local.tee 7
    i32.const -16
    i32.add
    local.tee 3
    global.set 0
    local.get 3
    local.get 1
    i32.const 8
    call 8
    drop
    local.get 4
    local.get 2
    i64.load
    i64.store offset=8
    local.get 7
    i32.const -8
    i32.add
    local.get 4
    i32.const 8
    i32.add
    i32.const 8
    call 8
    drop
    local.get 1
    i32.load offset=20
    i64.const 0
    local.get 3
    i32.const 16
    call 7
    block  ;; label = @1
      local.get 5
      local.get 0
      i64.load offset=16
      i64.lt_u
      br_if 0 (;@1;)
      local.get 0
      i32.const 16
      i32.add
      local.get 5
      i64.const 1
      i64.add
      i64.store
    end
    local.get 4
    i32.const 16
    i32.add
    global.set 0)
  (func (;66;) (type 22) (param i32 i32 i32 i32)
    (local i32 i32 i32 i32 i32)
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        i32.load offset=4
        local.get 0
        i32.load
        local.tee 4
        i32.sub
        i32.const 24
        i32.div_s
        local.tee 5
        i32.const 1
        i32.add
        local.tee 6
        i32.const 178956971
        i32.ge_u
        br_if 0 (;@2;)
        i32.const 178956970
        local.set 7
        block  ;; label = @3
          block  ;; label = @4
            local.get 0
            i32.load offset=8
            local.get 4
            i32.sub
            i32.const 24
            i32.div_s
            local.tee 4
            i32.const 89478484
            i32.gt_u
            br_if 0 (;@4;)
            local.get 6
            local.get 4
            i32.const 1
            i32.shl
            local.tee 7
            local.get 7
            local.get 6
            i32.lt_u
            select
            local.tee 7
            i32.eqz
            br_if 1 (;@3;)
          end
          local.get 7
          i32.const 24
          i32.mul
          call 45
          local.set 4
          br 2 (;@1;)
        end
        i32.const 0
        local.set 7
        i32.const 0
        local.set 4
        br 1 (;@1;)
      end
      local.get 0
      call 56
      unreachable
    end
    local.get 1
    i32.load
    local.set 6
    local.get 1
    i32.const 0
    i32.store
    local.get 4
    local.get 5
    i32.const 24
    i32.mul
    local.tee 8
    i32.add
    local.tee 1
    local.get 6
    i32.store
    local.get 1
    local.get 2
    i64.load
    i64.store offset=8
    local.get 1
    local.get 3
    i32.load
    i32.store offset=16
    local.get 4
    local.get 7
    i32.const 24
    i32.mul
    i32.add
    local.set 5
    local.get 1
    i32.const 24
    i32.add
    local.set 6
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        i32.const 4
        i32.add
        i32.load
        local.tee 2
        local.get 0
        i32.load
        local.tee 7
        i32.eq
        br_if 0 (;@2;)
        local.get 4
        local.get 8
        i32.add
        i32.const -24
        i32.add
        local.set 1
        loop  ;; label = @3
          local.get 2
          i32.const -24
          i32.add
          local.tee 4
          i32.load
          local.set 3
          local.get 4
          i32.const 0
          i32.store
          local.get 1
          local.get 3
          i32.store
          local.get 1
          i32.const 16
          i32.add
          local.get 2
          i32.const -8
          i32.add
          i32.load
          i32.store
          local.get 1
          i32.const 8
          i32.add
          local.get 2
          i32.const -16
          i32.add
          i64.load
          i64.store
          local.get 1
          i32.const -24
          i32.add
          local.set 1
          local.get 4
          local.set 2
          local.get 7
          local.get 4
          i32.ne
          br_if 0 (;@3;)
        end
        local.get 1
        i32.const 24
        i32.add
        local.set 1
        local.get 0
        i32.const 4
        i32.add
        i32.load
        local.set 7
        local.get 0
        i32.load
        local.set 2
        br 1 (;@1;)
      end
      local.get 7
      local.set 2
    end
    local.get 0
    local.get 1
    i32.store
    local.get 0
    i32.const 4
    i32.add
    local.get 6
    i32.store
    local.get 0
    i32.const 8
    i32.add
    local.get 5
    i32.store
    block  ;; label = @1
      local.get 7
      local.get 2
      i32.eq
      br_if 0 (;@1;)
      loop  ;; label = @2
        local.get 7
        i32.const -24
        i32.add
        local.tee 7
        i32.load
        local.set 1
        local.get 7
        i32.const 0
        i32.store
        block  ;; label = @3
          local.get 1
          i32.eqz
          br_if 0 (;@3;)
          local.get 1
          call 47
        end
        local.get 2
        local.get 7
        i32.ne
        br_if 0 (;@2;)
      end
    end
    block  ;; label = @1
      local.get 2
      i32.eqz
      br_if 0 (;@1;)
      local.get 2
      call 47
    end)
  (func (;67;) (type 21) (param i32 i32 i32)
    (local i32 i32 i64 i64 i64 i32 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 3
    global.set 0
    i32.const 0
    local.set 4
    local.get 1
    i64.load offset=8
    i64.const 8
    i64.shr_u
    local.tee 5
    local.set 6
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          loop  ;; label = @4
            local.get 6
            i32.wrap_i64
            i32.const 24
            i32.shl
            i32.const -1073741825
            i32.add
            i32.const 452984830
            i32.gt_u
            br_if 1 (;@3;)
            block  ;; label = @5
              local.get 6
              i64.const 8
              i64.shr_u
              local.set 7
              block  ;; label = @6
                local.get 6
                i64.const 65280
                i64.and
                i64.const 0
                i64.eq
                br_if 0 (;@6;)
                local.get 7
                local.set 6
                local.get 4
                local.tee 8
                i32.const 1
                i32.add
                local.set 4
                local.get 8
                i32.const 6
                i32.lt_s
                br_if 2 (;@4;)
                br 1 (;@5;)
              end
              local.get 7
              local.set 6
              loop  ;; label = @6
                local.get 6
                i64.const 65280
                i64.and
                i64.const 0
                i64.ne
                br_if 3 (;@3;)
                local.get 6
                i64.const 8
                i64.shr_u
                local.set 6
                local.get 4
                i32.const 6
                i32.lt_s
                local.set 8
                local.get 4
                i32.const 1
                i32.add
                local.tee 9
                local.set 4
                local.get 8
                br_if 0 (;@6;)
              end
              local.get 9
              i32.const 1
              i32.add
              local.set 4
              local.get 9
              i32.const 6
              i32.lt_s
              br_if 1 (;@4;)
            end
          end
          local.get 2
          i32.load8_u
          i32.const 1
          i32.and
          i32.eqz
          br_if 2 (;@1;)
          br 1 (;@2;)
        end
        i32.const 0
        i32.const 8245
        call 1
        local.get 2
        i32.load8_u
        i32.const 1
        i32.and
        i32.eqz
        br_if 1 (;@1;)
      end
      local.get 2
      i32.load offset=4
      i32.const 257
      i32.lt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8341
      call 1
    end
    i32.const 0
    local.set 2
    local.get 3
    i32.const 40
    i32.add
    i32.const 0
    i32.store
    local.get 3
    i64.const -1
    i64.store offset=24
    local.get 3
    i64.const 0
    i64.store offset=32
    local.get 3
    local.get 0
    i64.load
    local.tee 6
    i64.store offset=8
    local.get 3
    local.get 5
    i64.store offset=16
    block  ;; label = @1
      block  ;; label = @2
        local.get 6
        local.get 5
        i64.const -4157508551318700032
        local.get 5
        call 2
        local.tee 4
        i32.const 0
        i32.lt_s
        br_if 0 (;@2;)
        local.get 3
        i32.const 8
        i32.add
        local.get 4
        call 58
        local.tee 2
        i32.load offset=40
        local.get 3
        i32.const 8
        i32.add
        i32.eq
        br_if 1 (;@1;)
        i32.const 0
        i32.const 8959
        call 1
        br 1 (;@1;)
      end
      i32.const 0
      i32.const 8580
      call 1
    end
    local.get 2
    i64.load offset=32
    call 0
    block  ;; label = @1
      block  ;; label = @2
        local.get 1
        i64.load
        local.tee 5
        i64.const 4611686018427387903
        i64.add
        i64.const 9223372036854775806
        i64.gt_u
        br_if 0 (;@2;)
        local.get 1
        i32.const 8
        i32.add
        i64.load
        i64.const 8
        i64.shr_u
        local.set 6
        i32.const 0
        local.set 4
        loop  ;; label = @3
          local.get 6
          i32.wrap_i64
          i32.const 24
          i32.shl
          i32.const -1073741825
          i32.add
          i32.const 452984830
          i32.gt_u
          br_if 1 (;@2;)
          local.get 6
          i64.const 8
          i64.shr_u
          local.set 7
          block  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.eq
            br_if 0 (;@4;)
            local.get 7
            local.set 6
            local.get 4
            local.tee 8
            i32.const 1
            i32.add
            local.set 4
            local.get 8
            i32.const 6
            i32.lt_s
            br_if 1 (;@3;)
            br 3 (;@1;)
          end
          local.get 7
          local.set 6
          loop  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.ne
            br_if 2 (;@2;)
            local.get 6
            i64.const 8
            i64.shr_u
            local.set 6
            local.get 4
            i32.const 6
            i32.lt_s
            local.set 8
            local.get 4
            i32.const 1
            i32.add
            local.tee 9
            local.set 4
            local.get 8
            br_if 0 (;@4;)
          end
          local.get 9
          i32.const 1
          i32.add
          local.set 4
          local.get 9
          i32.const 6
          i32.lt_s
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      i32.const 0
      i32.const 8474
      call 1
      local.get 1
      i64.load
      local.set 5
    end
    block  ;; label = @1
      local.get 5
      i64.const 0
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8613
      call 1
    end
    block  ;; label = @1
      local.get 1
      i32.const 8
      i32.add
      i64.load
      local.get 2
      i64.load offset=8
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8520
      call 1
    end
    local.get 3
    local.get 1
    i32.store
    local.get 3
    i32.const 8
    i32.add
    local.get 2
    local.get 3
    call 68
    local.get 0
    local.get 2
    i32.const 32
    i32.add
    local.get 1
    call 69
    block  ;; label = @1
      local.get 3
      i32.load offset=32
      local.tee 9
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        block  ;; label = @3
          local.get 3
          i32.const 36
          i32.add
          local.tee 1
          i32.load
          local.tee 4
          local.get 9
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 4
            i32.const -24
            i32.add
            local.tee 4
            i32.load
            local.set 8
            local.get 4
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 8
              i32.eqz
              br_if 0 (;@5;)
              local.get 8
              call 47
            end
            local.get 9
            local.get 4
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 3
          i32.const 32
          i32.add
          i32.load
          local.set 4
          br 1 (;@2;)
        end
        local.get 9
        local.set 4
      end
      local.get 1
      local.get 9
      i32.store
      local.get 4
      call 47
    end
    local.get 3
    i32.const 48
    i32.add
    global.set 0)
  (func (;68;) (type 21) (param i32 i32 i32)
    (local i32 i32 i64 i64)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 3
    local.set 4
    local.get 3
    global.set 0
    block  ;; label = @1
      local.get 1
      i32.load offset=40
      local.get 0
      i32.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9090
      call 1
    end
    block  ;; label = @1
      call 3
      local.get 0
      i64.load
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9136
      call 1
    end
    block  ;; label = @1
      local.get 2
      i32.load
      local.tee 2
      i64.load offset=8
      local.get 1
      i64.load offset=8
      local.tee 5
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9326
      call 1
    end
    local.get 1
    local.get 1
    i64.load
    local.get 2
    i64.load
    i64.sub
    local.tee 6
    i64.store
    block  ;; label = @1
      local.get 6
      i64.const -4611686018427387904
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9374
      call 1
      local.get 1
      i64.load
      local.set 6
    end
    local.get 5
    i64.const 8
    i64.shr_u
    local.set 5
    block  ;; label = @1
      local.get 6
      i64.const 4611686018427387904
      i64.lt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9396
      call 1
    end
    block  ;; label = @1
      local.get 5
      local.get 1
      i32.const 8
      i32.add
      i64.load
      i64.const 8
      i64.shr_u
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9187
      call 1
    end
    local.get 3
    local.tee 2
    i32.const -48
    i32.add
    local.tee 3
    global.set 0
    local.get 4
    local.get 3
    i32.store offset=12
    local.get 4
    local.get 3
    i32.store offset=8
    local.get 4
    local.get 2
    i32.const -8
    i32.add
    i32.store offset=16
    local.get 4
    local.get 4
    i32.const 8
    i32.add
    i32.store offset=24
    local.get 4
    local.get 1
    i32.store offset=32
    local.get 4
    local.get 1
    i32.const 16
    i32.add
    i32.store offset=36
    local.get 4
    local.get 1
    i32.const 32
    i32.add
    i32.store offset=40
    local.get 4
    i32.const 32
    i32.add
    local.get 4
    i32.const 24
    i32.add
    call 59
    local.get 1
    i32.load offset=44
    i64.const 0
    local.get 3
    i32.const 40
    call 7
    block  ;; label = @1
      local.get 5
      local.get 0
      i64.load offset=16
      i64.lt_u
      br_if 0 (;@1;)
      local.get 0
      i32.const 16
      i32.add
      local.get 5
      i64.const 1
      i64.add
      i64.store
    end
    local.get 4
    i32.const 48
    i32.add
    global.set 0)
  (func (;69;) (type 21) (param i32 i32 i32)
    (local i32 i32 i64 i64)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 3
    global.set 0
    i32.const 0
    local.set 4
    local.get 3
    i32.const 40
    i32.add
    i32.const 0
    i32.store
    local.get 3
    i64.const -1
    i64.store offset=24
    local.get 3
    i64.const 0
    i64.store offset=32
    local.get 3
    local.get 0
    i64.load
    local.tee 5
    i64.store offset=8
    local.get 3
    local.get 1
    i64.load
    local.tee 6
    i64.store offset=16
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 5
          local.get 6
          i64.const 3607749779137757184
          local.get 2
          i64.load offset=8
          i64.const 8
          i64.shr_u
          call 2
          local.tee 0
          i32.const 0
          i32.lt_s
          br_if 0 (;@3;)
          block  ;; label = @4
            local.get 3
            i32.const 8
            i32.add
            local.get 0
            call 64
            local.tee 4
            i32.load offset=16
            local.get 3
            i32.const 8
            i32.add
            i32.eq
            br_if 0 (;@4;)
            i32.const 0
            i32.const 8959
            call 1
          end
          local.get 4
          i64.load
          local.get 2
          i64.load
          i64.ge_s
          br_if 2 (;@1;)
          br 1 (;@2;)
        end
        i32.const 0
        i32.const 8744
        call 1
        i32.const 0
        i64.load
        local.get 2
        i64.load
        i64.ge_s
        br_if 1 (;@1;)
      end
      i32.const 0
      i32.const 8768
      call 1
    end
    local.get 1
    i64.load
    local.set 5
    local.get 3
    local.get 2
    i32.store
    local.get 3
    i32.const 8
    i32.add
    local.get 4
    local.get 5
    local.get 3
    call 70
    block  ;; label = @1
      local.get 3
      i32.load offset=32
      local.tee 1
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        block  ;; label = @3
          local.get 3
          i32.const 36
          i32.add
          local.tee 0
          i32.load
          local.tee 2
          local.get 1
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 2
            i32.const -24
            i32.add
            local.tee 2
            i32.load
            local.set 4
            local.get 2
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 4
              i32.eqz
              br_if 0 (;@5;)
              local.get 4
              call 47
            end
            local.get 1
            local.get 2
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 3
          i32.const 32
          i32.add
          i32.load
          local.set 2
          br 1 (;@2;)
        end
        local.get 1
        local.set 2
      end
      local.get 0
      local.get 1
      i32.store
      local.get 2
      call 47
    end
    local.get 3
    i32.const 48
    i32.add
    global.set 0)
  (func (;70;) (type 23) (param i32 i32 i64 i32)
    (local i32 i32 i64 i64 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 4
    local.set 5
    local.get 4
    global.set 0
    block  ;; label = @1
      local.get 1
      i32.load offset=16
      local.get 0
      i32.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9090
      call 1
    end
    block  ;; label = @1
      call 3
      local.get 0
      i64.load
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9136
      call 1
    end
    block  ;; label = @1
      local.get 3
      i32.load
      local.tee 3
      i64.load offset=8
      local.get 1
      i64.load offset=8
      local.tee 6
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9326
      call 1
    end
    local.get 1
    local.get 1
    i64.load
    local.get 3
    i64.load
    i64.sub
    local.tee 7
    i64.store
    block  ;; label = @1
      local.get 7
      i64.const -4611686018427387904
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9374
      call 1
      local.get 1
      i64.load
      local.set 7
    end
    local.get 6
    i64.const 8
    i64.shr_u
    local.set 6
    block  ;; label = @1
      local.get 7
      i64.const 4611686018427387904
      i64.lt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9396
      call 1
    end
    block  ;; label = @1
      local.get 6
      local.get 1
      i32.const 8
      i32.add
      local.tee 3
      i64.load
      i64.const 8
      i64.shr_u
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9187
      call 1
    end
    local.get 4
    local.tee 8
    i32.const -16
    i32.add
    local.tee 4
    global.set 0
    local.get 4
    local.get 1
    i32.const 8
    call 8
    drop
    local.get 5
    local.get 3
    i64.load
    i64.store offset=8
    local.get 8
    i32.const -8
    i32.add
    local.get 5
    i32.const 8
    i32.add
    i32.const 8
    call 8
    drop
    local.get 1
    i32.load offset=20
    local.get 2
    local.get 4
    i32.const 16
    call 7
    block  ;; label = @1
      local.get 6
      local.get 0
      i64.load offset=16
      i64.lt_u
      br_if 0 (;@1;)
      local.get 0
      i32.const 16
      i32.add
      local.get 6
      i64.const 1
      i64.add
      i64.store
    end
    local.get 5
    i32.const 16
    i32.add
    global.set 0)
  (func (;71;) (type 24) (param i32 i32 i32 i32 i32)
    (local i32 i64 i32 i64 i32 i64 i32 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 5
    global.set 0
    block  ;; label = @1
      local.get 1
      i64.load
      local.tee 6
      local.get 2
      i64.load
      i64.ne
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8643
      call 1
      local.get 1
      i64.load
      local.set 6
    end
    local.get 6
    call 0
    block  ;; label = @1
      local.get 2
      i64.load
      call 9
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8667
      call 1
    end
    local.get 3
    i64.load offset=8
    local.set 6
    local.get 5
    i32.const 40
    i32.add
    i32.const 0
    i32.store
    local.get 5
    i64.const -1
    i64.store offset=24
    local.get 5
    i64.const 0
    i64.store offset=32
    local.get 5
    local.get 0
    i64.load
    i64.store offset=8
    local.get 5
    local.get 6
    i64.const 8
    i64.shr_u
    local.tee 6
    i64.store offset=16
    local.get 5
    i32.const 8
    i32.add
    local.get 6
    i32.const 8693
    call 72
    local.set 7
    local.get 1
    i64.load
    call 10
    local.get 2
    i64.load
    call 10
    block  ;; label = @1
      block  ;; label = @2
        local.get 3
        i64.load
        local.tee 8
        i64.const 4611686018427387903
        i64.add
        i64.const 9223372036854775806
        i64.gt_u
        br_if 0 (;@2;)
        local.get 3
        i32.const 8
        i32.add
        i64.load
        i64.const 8
        i64.shr_u
        local.set 6
        i32.const 0
        local.set 9
        loop  ;; label = @3
          local.get 6
          i32.wrap_i64
          i32.const 24
          i32.shl
          i32.const -1073741825
          i32.add
          i32.const 452984830
          i32.gt_u
          br_if 1 (;@2;)
          local.get 6
          i64.const 8
          i64.shr_u
          local.set 10
          block  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.eq
            br_if 0 (;@4;)
            local.get 10
            local.set 6
            local.get 9
            local.tee 11
            i32.const 1
            i32.add
            local.set 9
            local.get 11
            i32.const 6
            i32.lt_s
            br_if 1 (;@3;)
            br 3 (;@1;)
          end
          local.get 10
          local.set 6
          loop  ;; label = @4
            local.get 6
            i64.const 65280
            i64.and
            i64.const 0
            i64.ne
            br_if 2 (;@2;)
            local.get 6
            i64.const 8
            i64.shr_u
            local.set 6
            local.get 9
            i32.const 6
            i32.lt_s
            local.set 11
            local.get 9
            i32.const 1
            i32.add
            local.tee 12
            local.set 9
            local.get 11
            br_if 0 (;@4;)
          end
          local.get 12
          i32.const 1
          i32.add
          local.set 9
          local.get 12
          i32.const 6
          i32.lt_s
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      i32.const 0
      i32.const 8474
      call 1
      local.get 3
      i64.load
      local.set 8
    end
    block  ;; label = @1
      local.get 8
      i64.const 0
      i64.gt_s
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8712
      call 1
    end
    block  ;; label = @1
      local.get 3
      i32.const 8
      i32.add
      i64.load
      local.get 7
      i64.load offset=8
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8520
      call 1
    end
    block  ;; label = @1
      local.get 4
      i32.load8_u
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 4
      i32.load offset=4
      i32.const 257
      i32.lt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8341
      call 1
    end
    local.get 5
    local.get 2
    local.get 1
    local.get 2
    i64.load
    call 11
    select
    i64.load
    i64.store
    local.get 0
    local.get 1
    local.get 3
    call 69
    local.get 0
    local.get 2
    local.get 3
    local.get 5
    call 63
    block  ;; label = @1
      local.get 5
      i32.load offset=32
      local.tee 12
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        block  ;; label = @3
          local.get 5
          i32.const 36
          i32.add
          local.tee 3
          i32.load
          local.tee 9
          local.get 12
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 9
            i32.const -24
            i32.add
            local.tee 9
            i32.load
            local.set 11
            local.get 9
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 11
              i32.eqz
              br_if 0 (;@5;)
              local.get 11
              call 47
            end
            local.get 12
            local.get 9
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 5
          i32.const 32
          i32.add
          i32.load
          local.set 9
          br 1 (;@2;)
        end
        local.get 12
        local.set 9
      end
      local.get 3
      local.get 12
      i32.store
      local.get 9
      call 47
    end
    local.get 5
    i32.const 48
    i32.add
    global.set 0)
  (func (;72;) (type 25) (param i32 i64 i32) (result i32)
    (local i32 i32 i32 i32)
    block  ;; label = @1
      block  ;; label = @2
        local.get 0
        i32.load offset=24
        local.tee 3
        local.get 0
        i32.const 28
        i32.add
        i32.load
        local.tee 4
        i32.eq
        br_if 0 (;@2;)
        block  ;; label = @3
          loop  ;; label = @4
            local.get 4
            i32.const -24
            i32.add
            local.tee 5
            i32.load
            local.tee 6
            i64.load offset=8
            i64.const 8
            i64.shr_u
            local.get 1
            i64.eq
            br_if 1 (;@3;)
            local.get 5
            local.set 4
            local.get 3
            local.get 5
            i32.ne
            br_if 0 (;@4;)
            br 2 (;@2;)
          end
        end
        local.get 3
        local.get 4
        i32.eq
        br_if 0 (;@2;)
        local.get 6
        i32.load offset=40
        local.get 0
        i32.eq
        br_if 1 (;@1;)
        i32.const 0
        i32.const 8959
        call 1
        local.get 6
        return
      end
      i32.const 0
      local.set 6
      block  ;; label = @2
        local.get 0
        i64.load
        local.get 0
        i64.load offset=8
        i64.const -4157508551318700032
        local.get 1
        call 2
        local.tee 5
        i32.const 0
        i32.lt_s
        br_if 0 (;@2;)
        local.get 0
        local.get 5
        call 58
        local.tee 6
        i32.load offset=40
        local.get 0
        i32.eq
        br_if 1 (;@1;)
        i32.const 0
        i32.const 8959
        call 1
        local.get 6
        return
      end
      i32.const 0
      local.get 2
      call 1
    end
    local.get 6)
  (func (;73;) (type 22) (param i32 i32 i32 i32)
    (local i32 i64 i64 i64)
    global.get 0
    i32.const 128
    i32.sub
    local.tee 4
    global.set 0
    local.get 3
    i64.load
    call 0
    block  ;; label = @1
      local.get 1
      i64.load
      call 9
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8786
      call 1
    end
    local.get 2
    i64.load
    local.set 5
    local.get 4
    i32.const 48
    i32.add
    i32.const 32
    i32.add
    i32.const 0
    i32.store
    local.get 4
    local.get 5
    i64.const 8
    i64.shr_u
    local.tee 5
    i64.store offset=56
    local.get 4
    i64.const -1
    i64.store offset=64
    local.get 4
    i64.const 0
    i64.store offset=72
    local.get 4
    local.get 0
    i64.load
    i64.store offset=48
    block  ;; label = @1
      local.get 4
      i32.const 48
      i32.add
      local.get 5
      i32.const 8815
      call 72
      i64.load offset=8
      local.get 2
      i64.load
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 8520
      call 1
    end
    local.get 4
    i32.const 8
    i32.add
    i32.const 32
    i32.add
    i32.const 0
    i32.store
    local.get 4
    i64.const -1
    i64.store offset=24
    local.get 4
    i64.const 0
    i64.store offset=32
    local.get 4
    local.get 0
    i64.load
    local.tee 6
    i64.store offset=8
    local.get 4
    local.get 1
    i64.load
    local.tee 7
    i64.store offset=16
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            local.get 6
            local.get 7
            i64.const 3607749779137757184
            local.get 5
            call 2
            local.tee 0
            i32.const 0
            i32.lt_s
            br_if 0 (;@4;)
            local.get 4
            i32.const 8
            i32.add
            local.get 0
            call 64
            i32.load offset=16
            local.get 4
            i32.const 8
            i32.add
            i32.eq
            br_if 1 (;@3;)
            i32.const 0
            i32.const 8959
            call 1
            local.get 4
            i32.load offset=32
            local.tee 1
            br_if 2 (;@2;)
            br 3 (;@1;)
          end
          local.get 3
          i64.load
          local.set 5
          local.get 4
          local.get 2
          i32.store
          local.get 4
          local.get 5
          i64.store offset=120
          block  ;; label = @4
            call 3
            local.get 4
            i64.load offset=8
            i64.eq
            br_if 0 (;@4;)
            i32.const 0
            i32.const 9033
            call 1
          end
          local.get 4
          local.get 4
          i32.store offset=100
          local.get 4
          local.get 4
          i32.const 8
          i32.add
          i32.store offset=96
          local.get 4
          local.get 4
          i32.const 120
          i32.add
          i32.store offset=104
          i32.const 32
          call 45
          local.tee 2
          i64.const 0
          i64.store offset=8
          local.get 2
          i64.const 0
          i64.store
          local.get 2
          local.get 4
          i32.const 8
          i32.add
          i32.store offset=16
          local.get 4
          i32.const 96
          i32.add
          local.get 2
          call 74
          local.get 4
          local.get 2
          i32.store offset=112
          local.get 4
          local.get 2
          i64.load offset=8
          i64.const 8
          i64.shr_u
          local.tee 5
          i64.store offset=96
          local.get 4
          local.get 2
          i32.load offset=20
          local.tee 1
          i32.store offset=92
          block  ;; label = @4
            block  ;; label = @5
              local.get 4
              i32.const 36
              i32.add
              local.tee 3
              i32.load
              local.tee 0
              local.get 4
              i32.const 8
              i32.add
              i32.const 32
              i32.add
              i32.load
              i32.ge_u
              br_if 0 (;@5;)
              local.get 0
              local.get 5
              i64.store offset=8
              local.get 0
              local.get 1
              i32.store offset=16
              local.get 4
              i32.const 0
              i32.store offset=112
              local.get 0
              local.get 2
              i32.store
              local.get 3
              local.get 0
              i32.const 24
              i32.add
              i32.store
              local.get 4
              i32.load offset=112
              local.set 2
              local.get 4
              i32.const 0
              i32.store offset=112
              local.get 2
              br_if 1 (;@4;)
              br 2 (;@3;)
            end
            local.get 4
            i32.const 32
            i32.add
            local.get 4
            i32.const 112
            i32.add
            local.get 4
            i32.const 96
            i32.add
            local.get 4
            i32.const 92
            i32.add
            call 66
            local.get 4
            i32.load offset=112
            local.set 2
            local.get 4
            i32.const 0
            i32.store offset=112
            local.get 2
            i32.eqz
            br_if 1 (;@3;)
          end
          local.get 2
          call 47
        end
        local.get 4
        i32.load offset=32
        local.tee 1
        i32.eqz
        br_if 1 (;@1;)
      end
      block  ;; label = @2
        block  ;; label = @3
          local.get 4
          i32.const 36
          i32.add
          local.tee 3
          i32.load
          local.tee 2
          local.get 1
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 2
            i32.const -24
            i32.add
            local.tee 2
            i32.load
            local.set 0
            local.get 2
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 0
              i32.eqz
              br_if 0 (;@5;)
              local.get 0
              call 47
            end
            local.get 1
            local.get 2
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 4
          i32.const 32
          i32.add
          i32.load
          local.set 2
          br 1 (;@2;)
        end
        local.get 1
        local.set 2
      end
      local.get 3
      local.get 1
      i32.store
      local.get 2
      call 47
    end
    block  ;; label = @1
      local.get 4
      i32.load offset=72
      local.tee 1
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        block  ;; label = @3
          local.get 4
          i32.const 76
          i32.add
          local.tee 3
          i32.load
          local.tee 2
          local.get 1
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 2
            i32.const -24
            i32.add
            local.tee 2
            i32.load
            local.set 0
            local.get 2
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 0
              i32.eqz
              br_if 0 (;@5;)
              local.get 0
              call 47
            end
            local.get 1
            local.get 2
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 4
          i32.const 72
          i32.add
          i32.load
          local.set 2
          br 1 (;@2;)
        end
        local.get 1
        local.set 2
      end
      local.get 3
      local.get 1
      i32.store
      local.get 2
      call 47
    end
    local.get 4
    i32.const 128
    i32.add
    global.set 0)
  (func (;74;) (type 2) (param i32 i32)
    (local i32 i32 i64 i64 i32 i32 i64 i32 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    local.get 0
    i32.load offset=4
    i32.load
    i64.load
    local.tee 4
    i64.const 8
    i64.shr_u
    local.set 5
    local.get 0
    i32.load
    local.set 6
    i32.const 0
    local.set 7
    block  ;; label = @1
      block  ;; label = @2
        loop  ;; label = @3
          local.get 5
          i32.wrap_i64
          i32.const 24
          i32.shl
          i32.const -1073741825
          i32.add
          i32.const 452984830
          i32.gt_u
          br_if 1 (;@2;)
          local.get 5
          i64.const 8
          i64.shr_u
          local.set 8
          block  ;; label = @4
            local.get 5
            i64.const 65280
            i64.and
            i64.const 0
            i64.eq
            br_if 0 (;@4;)
            local.get 8
            local.set 5
            local.get 7
            local.tee 9
            i32.const 1
            i32.add
            local.set 7
            local.get 9
            i32.const 6
            i32.lt_s
            br_if 1 (;@3;)
            br 3 (;@1;)
          end
          local.get 8
          local.set 5
          loop  ;; label = @4
            local.get 5
            i64.const 65280
            i64.and
            i64.const 0
            i64.ne
            br_if 2 (;@2;)
            local.get 5
            i64.const 8
            i64.shr_u
            local.set 5
            local.get 7
            i32.const 6
            i32.lt_s
            local.set 9
            local.get 7
            i32.const 1
            i32.add
            local.tee 10
            local.set 7
            local.get 9
            br_if 0 (;@4;)
          end
          local.get 10
          i32.const 1
          i32.add
          local.set 7
          local.get 10
          i32.const 6
          i32.lt_s
          br_if 0 (;@3;)
          br 2 (;@1;)
        end
      end
      i32.const 0
      i32.const 8245
      call 1
    end
    local.get 1
    local.get 4
    i64.store offset=8
    local.get 1
    i64.const 0
    i64.store
    local.get 2
    local.tee 9
    i32.const -16
    i32.add
    local.tee 7
    global.set 0
    local.get 7
    local.get 1
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 1
    i64.load offset=8
    i64.store offset=8
    local.get 9
    i32.const -8
    i32.add
    local.get 3
    i32.const 8
    i32.add
    i32.const 8
    call 8
    drop
    local.get 1
    local.get 6
    i64.load offset=8
    i64.const 3607749779137757184
    local.get 0
    i32.load offset=8
    i64.load
    local.get 1
    i64.load offset=8
    i64.const 8
    i64.shr_u
    local.tee 5
    local.get 7
    i32.const 16
    call 6
    i32.store offset=20
    block  ;; label = @1
      local.get 5
      local.get 6
      i64.load offset=16
      i64.lt_u
      br_if 0 (;@1;)
      local.get 6
      i32.const 16
      i32.add
      local.get 5
      i64.const 1
      i64.add
      i64.store
    end
    local.get 3
    i32.const 16
    i32.add
    global.set 0)
  (func (;75;) (type 21) (param i32 i32 i32)
    (local i32 i32 i64 i64)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 3
    global.set 0
    local.get 1
    i64.load
    call 0
    i32.const 0
    local.set 4
    local.get 3
    i32.const 32
    i32.add
    i32.const 0
    i32.store
    local.get 3
    i64.const -1
    i64.store offset=16
    local.get 3
    i64.const 0
    i64.store offset=24
    local.get 3
    local.get 0
    i64.load
    local.tee 5
    i64.store
    local.get 3
    local.get 1
    i64.load
    local.tee 6
    i64.store offset=8
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          local.get 5
          local.get 6
          i64.const 3607749779137757184
          local.get 2
          i64.load
          i64.const 8
          i64.shr_u
          call 2
          local.tee 1
          i32.const -1
          i32.le_s
          br_if 0 (;@3;)
          block  ;; label = @4
            local.get 3
            local.get 1
            call 64
            local.tee 4
            i32.load offset=16
            local.get 3
            i32.eq
            br_if 0 (;@4;)
            i32.const 0
            i32.const 8959
            call 1
          end
          local.get 4
          i64.load
          i64.eqz
          br_if 2 (;@1;)
          br 1 (;@2;)
        end
        i32.const 0
        i32.const 8837
        call 1
        i32.const 0
        i64.load
        i64.eqz
        br_if 1 (;@1;)
      end
      i32.const 0
      i32.const 8913
      call 1
    end
    block  ;; label = @1
      local.get 4
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9417
      call 1
      i32.const 0
      i32.const 9451
      call 1
    end
    block  ;; label = @1
      local.get 4
      i32.load offset=20
      local.get 3
      i32.const 40
      i32.add
      call 12
      local.tee 1
      i32.const 0
      i32.lt_s
      br_if 0 (;@1;)
      local.get 3
      local.get 1
      call 64
      drop
    end
    local.get 3
    local.get 4
    call 76
    block  ;; label = @1
      local.get 3
      i32.load offset=24
      local.tee 2
      i32.eqz
      br_if 0 (;@1;)
      block  ;; label = @2
        block  ;; label = @3
          local.get 3
          i32.const 28
          i32.add
          local.tee 0
          i32.load
          local.tee 4
          local.get 2
          i32.eq
          br_if 0 (;@3;)
          loop  ;; label = @4
            local.get 4
            i32.const -24
            i32.add
            local.tee 4
            i32.load
            local.set 1
            local.get 4
            i32.const 0
            i32.store
            block  ;; label = @5
              local.get 1
              i32.eqz
              br_if 0 (;@5;)
              local.get 1
              call 47
            end
            local.get 2
            local.get 4
            i32.ne
            br_if 0 (;@4;)
          end
          local.get 3
          i32.const 24
          i32.add
          i32.load
          local.set 4
          br 1 (;@2;)
        end
        local.get 2
        local.set 4
      end
      local.get 0
      local.get 2
      i32.store
      local.get 4
      call 47
    end
    local.get 3
    i32.const 48
    i32.add
    global.set 0)
  (func (;76;) (type 2) (param i32 i32)
    (local i32 i32 i32 i32 i64 i32 i32 i32)
    block  ;; label = @1
      local.get 1
      i32.load offset=16
      local.get 0
      i32.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9481
      call 1
    end
    block  ;; label = @1
      call 3
      local.get 0
      i64.load
      i64.eq
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9526
      call 1
    end
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              block  ;; label = @6
                local.get 0
                i32.load offset=24
                local.tee 2
                local.get 0
                i32.const 28
                i32.add
                local.tee 3
                i32.load
                local.tee 4
                i32.eq
                br_if 0 (;@6;)
                local.get 4
                local.set 5
                block  ;; label = @7
                  local.get 4
                  i32.const -24
                  i32.add
                  i32.load
                  i64.load offset=8
                  local.get 1
                  i64.load offset=8
                  local.tee 6
                  i64.xor
                  i64.const 256
                  i64.lt_u
                  br_if 0 (;@7;)
                  local.get 2
                  i32.const 24
                  i32.add
                  local.set 7
                  local.get 4
                  local.set 8
                  loop  ;; label = @8
                    local.get 7
                    local.get 8
                    i32.eq
                    br_if 2 (;@6;)
                    local.get 8
                    i32.const -48
                    i32.add
                    local.set 9
                    local.get 8
                    i32.const -24
                    i32.add
                    local.tee 5
                    local.set 8
                    local.get 9
                    i32.load
                    i64.load offset=8
                    local.get 6
                    i64.xor
                    i64.const 256
                    i64.ge_u
                    br_if 0 (;@8;)
                  end
                end
                local.get 2
                local.get 5
                i32.eq
                br_if 1 (;@5;)
                i32.const -24
                local.set 9
                local.get 5
                local.get 4
                i32.eq
                br_if 2 (;@4;)
                br 3 (;@3;)
              end
              local.get 2
              local.set 5
            end
            i32.const 0
            i32.const 9576
            call 1
            i32.const -24
            local.set 9
            local.get 5
            local.get 3
            i32.load
            local.tee 4
            i32.ne
            br_if 1 (;@3;)
          end
          local.get 5
          local.get 9
          i32.add
          local.set 7
          br 1 (;@2;)
        end
        local.get 5
        local.set 8
        loop  ;; label = @3
          local.get 8
          i32.load
          local.set 7
          local.get 8
          i32.const 0
          i32.store
          local.get 8
          local.get 9
          i32.add
          local.tee 2
          i32.load
          local.set 5
          local.get 2
          local.get 7
          i32.store
          block  ;; label = @4
            local.get 5
            i32.eqz
            br_if 0 (;@4;)
            local.get 5
            call 47
          end
          local.get 8
          i32.const -8
          i32.add
          local.get 8
          i32.const 16
          i32.add
          i32.load
          i32.store
          local.get 8
          i32.const -16
          i32.add
          local.get 8
          i32.const 8
          i32.add
          i64.load
          i64.store
          local.get 4
          local.get 8
          i32.const 24
          i32.add
          local.tee 8
          i32.ne
          br_if 0 (;@3;)
        end
        local.get 8
        i32.const -24
        i32.add
        local.set 7
        local.get 0
        i32.const 28
        i32.add
        i32.load
        local.tee 5
        i32.const 24
        i32.add
        local.get 8
        i32.eq
        br_if 1 (;@1;)
      end
      loop  ;; label = @2
        local.get 5
        local.get 9
        i32.add
        local.tee 5
        i32.load
        local.set 8
        local.get 5
        i32.const 0
        i32.store
        block  ;; label = @3
          local.get 8
          i32.eqz
          br_if 0 (;@3;)
          local.get 8
          call 47
        end
        local.get 7
        local.get 5
        i32.ne
        br_if 0 (;@2;)
      end
    end
    local.get 0
    i32.const 28
    i32.add
    local.get 7
    i32.store
    local.get 1
    i32.load offset=20
    call 36)
  (func (;77;) (type 26) (param i64 i64)
    (local i32 i32 i32 i32 i32)
    global.get 0
    i32.const 64
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            call 13
            local.tee 4
            i32.eqz
            br_if 0 (;@4;)
            local.get 4
            i32.const 512
            i32.lt_u
            br_if 1 (;@3;)
            local.get 4
            call 39
            local.set 2
            br 2 (;@2;)
          end
          i32.const 0
          local.set 2
          br 2 (;@1;)
        end
        local.get 2
        local.get 4
        i32.const 15
        i32.add
        i32.const -16
        i32.and
        i32.sub
        local.tee 2
        global.set 0
      end
      local.get 2
      local.get 4
      call 14
      drop
    end
    local.get 3
    i64.const 0
    i64.store offset=56
    block  ;; label = @1
      local.get 4
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 3
    i32.const 56
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    i64.const 0
    i64.store offset=48
    local.get 3
    i64.const 0
    i64.store offset=40
    local.get 2
    i32.const 8
    i32.add
    local.set 5
    block  ;; label = @1
      local.get 4
      i32.const -8
      i32.and
      local.tee 6
      i32.const 8
      i32.ne
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 2
    local.get 4
    i32.add
    local.set 4
    local.get 3
    i32.const 40
    i32.add
    local.get 5
    i32.const 8
    call 8
    drop
    local.get 3
    i64.const 0
    i64.store offset=8
    local.get 2
    i32.const 16
    i32.add
    local.set 5
    block  ;; label = @1
      local.get 6
      i32.const 16
      i32.ne
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 3
    i32.const 8
    i32.add
    local.get 5
    i32.const 8
    call 8
    drop
    local.get 3
    i32.const 40
    i32.add
    i32.const 8
    i32.add
    local.get 3
    i64.load offset=8
    i64.store
    local.get 3
    i32.const 8
    i32.add
    i32.const 24
    i32.add
    local.get 4
    i32.store
    local.get 3
    local.get 2
    i32.store offset=24
    local.get 3
    i32.const 28
    i32.add
    local.get 2
    i32.const 24
    i32.add
    i32.store
    local.get 3
    local.get 1
    i64.store offset=16
    local.get 3
    local.get 0
    i64.store offset=8
    local.get 3
    i32.const 8
    i32.add
    local.get 3
    i32.const 56
    i32.add
    local.get 3
    i32.const 40
    i32.add
    call 57
    local.get 3
    i32.const 64
    i32.add
    global.set 0)
  (func (;78;) (type 26) (param i64 i64)
    (local i32 i32 i32 i32)
    global.get 0
    i32.const 144
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            call 13
            local.tee 4
            i32.eqz
            br_if 0 (;@4;)
            local.get 4
            i32.const 512
            i32.lt_u
            br_if 1 (;@3;)
            local.get 4
            call 39
            local.set 2
            br 2 (;@2;)
          end
          i32.const 0
          local.set 2
          br 2 (;@1;)
        end
        local.get 2
        local.get 4
        i32.const 15
        i32.add
        i32.const -16
        i32.and
        i32.sub
        local.tee 2
        global.set 0
      end
      local.get 2
      local.get 4
      call 14
      drop
    end
    local.get 3
    local.get 2
    i32.store offset=100
    local.get 3
    local.get 2
    i32.store offset=96
    local.get 3
    local.get 2
    local.get 4
    i32.add
    local.tee 5
    i32.store offset=104
    local.get 3
    i64.const 0
    i64.store offset=88
    block  ;; label = @1
      local.get 4
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.const 104
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.load offset=100
      local.set 2
    end
    local.get 3
    i32.const 88
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    local.tee 2
    i32.store offset=100
    local.get 3
    i64.const 0
    i64.store offset=80
    local.get 3
    i64.const 0
    i64.store offset=72
    block  ;; label = @1
      local.get 5
      local.get 2
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.const 96
      i32.add
      i32.const 8
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.load offset=100
      local.set 2
    end
    local.get 3
    i32.const 72
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    local.tee 2
    i32.store offset=100
    local.get 3
    i64.const 0
    i64.store offset=24
    block  ;; label = @1
      local.get 5
      local.get 2
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.load offset=100
      local.set 2
    end
    local.get 3
    i32.const 24
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    i32.const 72
    i32.add
    i32.const 8
    i32.add
    local.get 3
    i64.load offset=24
    i64.store
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    i32.store offset=100
    local.get 3
    i32.const 0
    i32.store offset=64
    local.get 3
    i64.const 0
    i64.store offset=56
    local.get 3
    i32.const 96
    i32.add
    local.get 3
    i32.const 56
    i32.add
    call 79
    drop
    local.get 3
    i32.const 8
    i32.add
    i32.const 8
    i32.add
    local.tee 2
    local.get 3
    i32.const 96
    i32.add
    i32.const 8
    i32.add
    i32.load
    i32.store
    local.get 3
    local.get 3
    i64.load offset=96
    i64.store offset=8
    local.get 3
    i32.const 112
    i32.add
    i32.const 8
    i32.add
    local.tee 4
    local.get 2
    i32.load
    i32.store
    local.get 3
    local.get 3
    i64.load offset=8
    i64.store offset=112
    local.get 3
    i32.const 128
    i32.add
    i32.const 8
    i32.add
    local.get 4
    i32.load
    local.tee 2
    i32.store
    local.get 3
    i32.const 48
    i32.add
    local.get 2
    i32.store
    local.get 3
    local.get 0
    i64.store offset=24
    local.get 3
    local.get 1
    i64.store offset=32
    local.get 3
    local.get 3
    i64.load offset=112
    local.tee 0
    i64.store offset=40
    local.get 3
    local.get 0
    i64.store offset=128
    local.get 3
    i32.const 24
    i32.add
    local.get 3
    i32.const 88
    i32.add
    local.get 3
    i32.const 72
    i32.add
    local.get 3
    i32.const 56
    i32.add
    call 61
    block  ;; label = @1
      local.get 3
      i32.load8_u offset=56
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 3
      i32.const 56
      i32.add
      i32.const 8
      i32.add
      i32.load
      call 47
    end
    local.get 3
    i32.const 144
    i32.add
    global.set 0)
  (func (;79;) (type 9) (param i32 i32) (result i32)
    (local i32 i32 i32 i32 i32 i32)
    global.get 0
    i32.const 32
    i32.sub
    local.tee 2
    global.set 0
    local.get 2
    i32.const 0
    i32.store offset=24
    local.get 2
    i64.const 0
    i64.store offset=16
    local.get 0
    local.get 2
    i32.const 16
    i32.add
    call 80
    drop
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              block  ;; label = @6
                block  ;; label = @7
                  block  ;; label = @8
                    local.get 2
                    i32.load offset=20
                    local.get 2
                    i32.load offset=16
                    local.tee 3
                    i32.sub
                    local.tee 4
                    i32.eqz
                    br_if 0 (;@8;)
                    local.get 2
                    i32.const 8
                    i32.add
                    i32.const 0
                    i32.store
                    local.get 2
                    i64.const 0
                    i64.store
                    local.get 4
                    i32.const -16
                    i32.ge_u
                    br_if 5 (;@3;)
                    local.get 4
                    i32.const 10
                    i32.gt_u
                    br_if 1 (;@7;)
                    local.get 2
                    local.get 4
                    i32.const 1
                    i32.shl
                    i32.store8
                    local.get 2
                    i32.const 1
                    i32.or
                    local.set 5
                    br 2 (;@6;)
                  end
                  local.get 1
                  i32.load8_u
                  i32.const 1
                  i32.and
                  br_if 2 (;@5;)
                  local.get 1
                  i32.const 0
                  i32.store16
                  local.get 1
                  i32.const 8
                  i32.add
                  local.set 3
                  br 3 (;@4;)
                end
                local.get 4
                i32.const 16
                i32.add
                i32.const -16
                i32.and
                local.tee 6
                call 45
                local.set 5
                local.get 2
                local.get 6
                i32.const 1
                i32.or
                i32.store
                local.get 2
                local.get 5
                i32.store offset=8
                local.get 2
                local.get 4
                i32.store offset=4
              end
              local.get 4
              local.set 7
              local.get 5
              local.set 6
              loop  ;; label = @6
                local.get 6
                local.get 3
                i32.load8_u
                i32.store8
                local.get 6
                i32.const 1
                i32.add
                local.set 6
                local.get 3
                i32.const 1
                i32.add
                local.set 3
                local.get 7
                i32.const -1
                i32.add
                local.tee 7
                br_if 0 (;@6;)
              end
              local.get 5
              local.get 4
              i32.add
              i32.const 0
              i32.store8
              block  ;; label = @6
                block  ;; label = @7
                  local.get 1
                  i32.load8_u
                  i32.const 1
                  i32.and
                  br_if 0 (;@7;)
                  local.get 1
                  i32.const 0
                  i32.store16
                  br 1 (;@6;)
                end
                local.get 1
                i32.load offset=8
                i32.const 0
                i32.store8
                local.get 1
                i32.const 0
                i32.store offset=4
              end
              local.get 1
              i32.const 0
              call 54
              local.get 1
              i32.const 8
              i32.add
              local.get 2
              i32.const 8
              i32.add
              i32.load
              i32.store
              local.get 1
              local.get 2
              i64.load
              i64.store align=4
              local.get 2
              i32.load offset=16
              local.tee 3
              i32.eqz
              br_if 4 (;@1;)
              br 3 (;@2;)
            end
            local.get 1
            i32.load offset=8
            i32.const 0
            i32.store8
            local.get 1
            i32.const 0
            i32.store offset=4
            local.get 1
            i32.const 8
            i32.add
            local.set 3
          end
          local.get 1
          i32.const 0
          call 54
          local.get 3
          i32.const 0
          i32.store
          local.get 1
          i64.const 0
          i64.store align=4
          local.get 2
          i32.load offset=16
          local.tee 3
          br_if 1 (;@2;)
          br 2 (;@1;)
        end
        local.get 2
        call 53
        unreachable
      end
      local.get 2
      local.get 3
      i32.store offset=20
      local.get 3
      call 47
    end
    local.get 2
    i32.const 32
    i32.add
    global.set 0
    local.get 0)
  (func (;80;) (type 9) (param i32 i32) (result i32)
    (local i32 i64 i32 i32 i32 i32 i32)
    local.get 0
    i32.load offset=4
    local.set 2
    i64.const 0
    local.set 3
    local.get 0
    i32.const 8
    i32.add
    local.set 4
    local.get 0
    i32.const 4
    i32.add
    local.set 5
    i32.const 0
    local.set 6
    loop  ;; label = @1
      block  ;; label = @2
        local.get 2
        local.get 4
        i32.load
        i32.lt_u
        br_if 0 (;@2;)
        i32.const 0
        i32.const 9634
        call 1
        local.get 5
        i32.load
        local.set 2
      end
      local.get 2
      i32.load8_u
      local.set 7
      local.get 5
      local.get 2
      i32.const 1
      i32.add
      local.tee 8
      i32.store
      local.get 3
      local.get 7
      i32.const 127
      i32.and
      local.get 6
      i32.const 255
      i32.and
      local.tee 2
      i32.shl
      i64.extend_i32_u
      i64.or
      local.set 3
      local.get 2
      i32.const 7
      i32.add
      local.set 6
      local.get 8
      local.set 2
      local.get 7
      i32.const 128
      i32.and
      br_if 0 (;@1;)
    end
    block  ;; label = @1
      block  ;; label = @2
        local.get 1
        i32.load offset=4
        local.tee 7
        local.get 1
        i32.load
        local.tee 2
        i32.sub
        local.tee 5
        local.get 3
        i32.wrap_i64
        local.tee 6
        i32.ge_u
        br_if 0 (;@2;)
        local.get 1
        local.get 6
        local.get 5
        i32.sub
        call 86
        local.get 0
        i32.const 4
        i32.add
        i32.load
        local.set 8
        local.get 1
        i32.const 4
        i32.add
        i32.load
        local.set 7
        local.get 1
        i32.load
        local.set 2
        br 1 (;@1;)
      end
      local.get 5
      local.get 6
      i32.le_u
      br_if 0 (;@1;)
      local.get 1
      i32.const 4
      i32.add
      local.get 2
      local.get 6
      i32.add
      local.tee 7
      i32.store
    end
    block  ;; label = @1
      local.get 0
      i32.const 8
      i32.add
      i32.load
      local.get 8
      i32.sub
      local.get 7
      local.get 2
      i32.sub
      local.tee 7
      i32.ge_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 0
      i32.const 4
      i32.add
      i32.load
      local.set 8
    end
    local.get 2
    local.get 8
    local.get 7
    call 8
    drop
    local.get 0
    i32.const 4
    i32.add
    local.tee 2
    local.get 2
    i32.load
    local.get 7
    i32.add
    i32.store
    local.get 0)
  (func (;81;) (type 26) (param i64 i64)
    (local i32 i32 i32 i32)
    global.get 0
    i32.const 128
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            call 13
            local.tee 4
            i32.eqz
            br_if 0 (;@4;)
            local.get 4
            i32.const 512
            i32.lt_u
            br_if 1 (;@3;)
            local.get 4
            call 39
            local.set 2
            br 2 (;@2;)
          end
          i32.const 0
          local.set 2
          br 2 (;@1;)
        end
        local.get 2
        local.get 4
        i32.const 15
        i32.add
        i32.const -16
        i32.and
        i32.sub
        local.tee 2
        global.set 0
      end
      local.get 2
      local.get 4
      call 14
      drop
    end
    local.get 3
    local.get 2
    i32.store offset=84
    local.get 3
    local.get 2
    i32.store offset=80
    local.get 3
    local.get 2
    local.get 4
    i32.add
    local.tee 5
    i32.store offset=88
    local.get 3
    i64.const 0
    i64.store offset=72
    local.get 3
    i64.const 0
    i64.store offset=64
    block  ;; label = @1
      local.get 4
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.const 88
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.load offset=84
      local.set 2
    end
    local.get 3
    i32.const 64
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    local.tee 2
    i32.store offset=84
    local.get 3
    i64.const 0
    i64.store offset=16
    block  ;; label = @1
      local.get 5
      local.get 2
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.load offset=84
      local.set 2
    end
    local.get 3
    i32.const 16
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    i32.const 64
    i32.add
    i32.const 8
    i32.add
    local.get 3
    i64.load offset=16
    i64.store
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    i32.store offset=84
    local.get 3
    i32.const 0
    i32.store offset=56
    local.get 3
    i64.const 0
    i64.store offset=48
    local.get 3
    i32.const 80
    i32.add
    local.get 3
    i32.const 48
    i32.add
    call 79
    drop
    local.get 3
    i32.const 8
    i32.add
    local.tee 2
    local.get 3
    i32.const 80
    i32.add
    i32.const 8
    i32.add
    i32.load
    i32.store
    local.get 3
    local.get 3
    i64.load offset=80
    i64.store
    local.get 3
    i32.const 96
    i32.add
    i32.const 8
    i32.add
    local.tee 4
    local.get 2
    i32.load
    i32.store
    local.get 3
    local.get 3
    i64.load
    i64.store offset=96
    local.get 3
    i32.const 112
    i32.add
    i32.const 8
    i32.add
    local.get 4
    i32.load
    local.tee 2
    i32.store
    local.get 3
    i32.const 40
    i32.add
    local.get 2
    i32.store
    local.get 3
    local.get 0
    i64.store offset=16
    local.get 3
    local.get 1
    i64.store offset=24
    local.get 3
    local.get 3
    i64.load offset=96
    local.tee 0
    i64.store offset=32
    local.get 3
    local.get 0
    i64.store offset=112
    local.get 3
    i32.const 16
    i32.add
    local.get 3
    i32.const 64
    i32.add
    local.get 3
    i32.const 48
    i32.add
    call 67
    block  ;; label = @1
      local.get 3
      i32.load8_u offset=48
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 3
      i32.const 56
      i32.add
      i32.load
      call 47
    end
    local.get 3
    i32.const 128
    i32.add
    global.set 0)
  (func (;82;) (type 26) (param i64 i64)
    (local i32 i32 i32 i32)
    global.get 0
    i32.const 144
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            call 13
            local.tee 4
            i32.eqz
            br_if 0 (;@4;)
            local.get 4
            i32.const 512
            i32.lt_u
            br_if 1 (;@3;)
            local.get 4
            call 39
            local.set 2
            br 2 (;@2;)
          end
          i32.const 0
          local.set 2
          br 2 (;@1;)
        end
        local.get 2
        local.get 4
        i32.const 15
        i32.add
        i32.const -16
        i32.and
        i32.sub
        local.tee 2
        global.set 0
      end
      local.get 2
      local.get 4
      call 14
      drop
    end
    local.get 3
    local.get 2
    i32.store offset=100
    local.get 3
    local.get 2
    i32.store offset=96
    local.get 3
    local.get 2
    local.get 4
    i32.add
    local.tee 5
    i32.store offset=104
    local.get 3
    i64.const 0
    i64.store offset=88
    block  ;; label = @1
      local.get 4
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.const 104
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.load offset=100
      local.set 2
    end
    local.get 3
    i32.const 88
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    local.tee 2
    i32.store offset=100
    local.get 3
    i64.const 0
    i64.store offset=80
    block  ;; label = @1
      local.get 5
      local.get 2
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.const 96
      i32.add
      i32.const 8
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.load offset=100
      local.set 2
    end
    local.get 3
    i32.const 80
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    local.tee 2
    i32.store offset=100
    local.get 3
    i64.const 0
    i64.store offset=72
    local.get 3
    i64.const 0
    i64.store offset=64
    block  ;; label = @1
      local.get 5
      local.get 2
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.const 104
      i32.add
      i32.load
      local.set 5
      local.get 3
      i32.load offset=100
      local.set 2
    end
    local.get 3
    i32.const 64
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    local.tee 2
    i32.store offset=100
    local.get 3
    i64.const 0
    i64.store offset=16
    block  ;; label = @1
      local.get 5
      local.get 2
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 3
      i32.load offset=100
      local.set 2
    end
    local.get 3
    i32.const 16
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    i32.const 64
    i32.add
    i32.const 8
    i32.add
    local.get 3
    i64.load offset=16
    i64.store
    local.get 3
    local.get 2
    i32.const 8
    i32.add
    i32.store offset=100
    local.get 3
    i32.const 0
    i32.store offset=56
    local.get 3
    i64.const 0
    i64.store offset=48
    local.get 3
    i32.const 96
    i32.add
    local.get 3
    i32.const 48
    i32.add
    call 79
    drop
    local.get 3
    i32.const 8
    i32.add
    local.tee 2
    local.get 3
    i32.const 96
    i32.add
    i32.const 8
    i32.add
    i32.load
    i32.store
    local.get 3
    local.get 3
    i64.load offset=96
    i64.store
    local.get 3
    i32.const 112
    i32.add
    i32.const 8
    i32.add
    local.tee 5
    local.get 2
    i32.load
    i32.store
    local.get 3
    local.get 3
    i64.load
    i64.store offset=112
    local.get 3
    i32.const 128
    i32.add
    i32.const 8
    i32.add
    local.get 5
    i32.load
    local.tee 2
    i32.store
    local.get 3
    i32.const 40
    i32.add
    local.get 2
    i32.store
    local.get 3
    local.get 0
    i64.store offset=16
    local.get 3
    local.get 1
    i64.store offset=24
    local.get 3
    local.get 3
    i64.load offset=112
    local.tee 0
    i64.store offset=32
    local.get 3
    local.get 0
    i64.store offset=128
    local.get 3
    i32.const 16
    i32.add
    local.get 3
    i32.const 88
    i32.add
    local.get 3
    i32.const 80
    i32.add
    local.get 3
    i32.const 64
    i32.add
    local.get 3
    i32.const 48
    i32.add
    call 71
    block  ;; label = @1
      local.get 3
      i32.load8_u offset=48
      i32.const 1
      i32.and
      i32.eqz
      br_if 0 (;@1;)
      local.get 3
      i32.const 56
      i32.add
      i32.load
      call 47
    end
    local.get 3
    i32.const 144
    i32.add
    global.set 0)
  (func (;83;) (type 26) (param i64 i64)
    (local i32 i32 i32 i32 i32)
    global.get 0
    i32.const 64
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            call 13
            local.tee 4
            i32.eqz
            br_if 0 (;@4;)
            local.get 4
            i32.const 512
            i32.lt_u
            br_if 1 (;@3;)
            local.get 4
            call 39
            local.set 2
            br 2 (;@2;)
          end
          i32.const 0
          local.set 2
          br 2 (;@1;)
        end
        local.get 2
        local.get 4
        i32.const 15
        i32.add
        i32.const -16
        i32.and
        i32.sub
        local.tee 2
        global.set 0
      end
      local.get 2
      local.get 4
      call 14
      drop
    end
    local.get 3
    i64.const 0
    i64.store offset=56
    block  ;; label = @1
      local.get 4
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 3
    i32.const 56
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    i64.const 0
    i64.store offset=48
    local.get 3
    i64.const 0
    i64.store offset=8
    local.get 2
    i32.const 8
    i32.add
    local.set 5
    block  ;; label = @1
      local.get 4
      i32.const -8
      i32.and
      local.tee 6
      i32.const 8
      i32.ne
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 2
    local.get 4
    i32.add
    local.set 4
    local.get 3
    i32.const 8
    i32.add
    local.get 5
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 3
    i64.load offset=8
    i64.store offset=48
    local.get 3
    i64.const 0
    i64.store offset=40
    local.get 2
    i32.const 16
    i32.add
    local.set 5
    block  ;; label = @1
      local.get 6
      i32.const 16
      i32.ne
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 3
    i32.const 40
    i32.add
    local.get 5
    i32.const 8
    call 8
    drop
    local.get 3
    i32.const 8
    i32.add
    i32.const 24
    i32.add
    local.get 4
    i32.store
    local.get 3
    local.get 2
    i32.store offset=24
    local.get 3
    i32.const 28
    i32.add
    local.get 2
    i32.const 24
    i32.add
    i32.store
    local.get 3
    local.get 1
    i64.store offset=16
    local.get 3
    local.get 0
    i64.store offset=8
    local.get 3
    i32.const 8
    i32.add
    local.get 3
    i32.const 56
    i32.add
    local.get 3
    i32.const 48
    i32.add
    local.get 3
    i32.const 40
    i32.add
    call 73
    local.get 3
    i32.const 64
    i32.add
    global.set 0)
  (func (;84;) (type 26) (param i64 i64)
    (local i32 i32 i32 i32 i32)
    global.get 0
    i32.const 48
    i32.sub
    local.tee 2
    local.set 3
    local.get 2
    global.set 0
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            call 13
            local.tee 4
            i32.eqz
            br_if 0 (;@4;)
            local.get 4
            i32.const 512
            i32.lt_u
            br_if 1 (;@3;)
            local.get 4
            call 39
            local.set 2
            br 2 (;@2;)
          end
          i32.const 0
          local.set 2
          br 2 (;@1;)
        end
        local.get 2
        local.get 4
        i32.const 15
        i32.add
        i32.const -16
        i32.and
        i32.sub
        local.tee 2
        global.set 0
      end
      local.get 2
      local.get 4
      call 14
      drop
    end
    local.get 3
    i64.const 0
    i64.store offset=40
    block  ;; label = @1
      local.get 4
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 2
    local.get 4
    i32.add
    local.set 5
    local.get 3
    i32.const 40
    i32.add
    local.get 2
    i32.const 8
    call 8
    drop
    local.get 3
    i64.const 0
    i64.store offset=32
    local.get 3
    i64.const 0
    i64.store
    local.get 2
    i32.const 8
    i32.add
    local.set 6
    block  ;; label = @1
      local.get 4
      i32.const -8
      i32.and
      i32.const 8
      i32.ne
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
    end
    local.get 3
    local.get 6
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 3
    i64.load
    i64.store offset=32
    local.get 3
    i32.const 24
    i32.add
    local.get 5
    i32.store
    local.get 3
    local.get 2
    i32.store offset=16
    local.get 3
    i32.const 20
    i32.add
    local.get 2
    i32.const 16
    i32.add
    i32.store
    local.get 3
    local.get 1
    i64.store offset=8
    local.get 3
    local.get 0
    i64.store
    local.get 3
    local.get 3
    i32.const 40
    i32.add
    local.get 3
    i32.const 32
    i32.add
    call 75
    local.get 3
    i32.const 48
    i32.add
    global.set 0)
  (func (;85;) (type 2) (param i32 i32)
    (local i32 i32 i32 i32 i32)
    global.get 0
    i32.const 16
    i32.sub
    local.tee 2
    global.set 0
    local.get 0
    i32.load
    local.set 3
    block  ;; label = @1
      local.get 1
      i32.load
      local.tee 4
      i32.load offset=8
      local.get 4
      i32.load offset=4
      local.tee 5
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 4
      i32.const 4
      i32.add
      i32.load
      local.set 5
    end
    local.get 3
    local.get 5
    i32.const 8
    call 8
    drop
    local.get 4
    i32.const 4
    i32.add
    local.tee 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    local.tee 6
    i32.store
    local.get 2
    i64.const 0
    i64.store offset=8
    block  ;; label = @1
      local.get 4
      i32.const 8
      i32.add
      i32.load
      local.get 6
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 5
      i32.load
      local.set 6
    end
    local.get 2
    i32.const 8
    i32.add
    local.get 6
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i64.load offset=8
    i64.store offset=8
    local.get 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    i32.store
    local.get 0
    i32.load offset=4
    local.set 3
    block  ;; label = @1
      local.get 1
      i32.load
      local.tee 4
      i32.load offset=8
      local.get 4
      i32.load offset=4
      local.tee 5
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 4
      i32.const 4
      i32.add
      i32.load
      local.set 5
    end
    local.get 3
    local.get 5
    i32.const 8
    call 8
    drop
    local.get 4
    i32.const 4
    i32.add
    local.tee 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    local.tee 6
    i32.store
    local.get 2
    i64.const 0
    i64.store offset=8
    block  ;; label = @1
      local.get 4
      i32.const 8
      i32.add
      i32.load
      local.get 6
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 5
      i32.load
      local.set 6
    end
    local.get 2
    i32.const 8
    i32.add
    local.get 6
    i32.const 8
    call 8
    drop
    local.get 3
    local.get 2
    i64.load offset=8
    i64.store offset=8
    local.get 5
    local.get 5
    i32.load
    i32.const 8
    i32.add
    i32.store
    local.get 0
    i32.load offset=8
    local.set 0
    block  ;; label = @1
      local.get 1
      i32.load
      local.tee 4
      i32.load offset=8
      local.get 4
      i32.load offset=4
      local.tee 5
      i32.sub
      i32.const 7
      i32.gt_u
      br_if 0 (;@1;)
      i32.const 0
      i32.const 9629
      call 1
      local.get 4
      i32.const 4
      i32.add
      i32.load
      local.set 5
    end
    local.get 0
    local.get 5
    i32.const 8
    call 8
    drop
    local.get 4
    i32.const 4
    i32.add
    local.tee 4
    local.get 4
    i32.load
    i32.const 8
    i32.add
    i32.store
    local.get 2
    i32.const 16
    i32.add
    global.set 0)
  (func (;86;) (type 2) (param i32 i32)
    (local i32 i32 i32 i32 i32 i32)
    block  ;; label = @1
      block  ;; label = @2
        block  ;; label = @3
          block  ;; label = @4
            block  ;; label = @5
              local.get 0
              i32.load offset=8
              local.tee 2
              local.get 0
              i32.load offset=4
              local.tee 3
              i32.sub
              local.get 1
              i32.ge_u
              br_if 0 (;@5;)
              local.get 3
              local.get 0
              i32.load
              local.tee 4
              i32.sub
              local.tee 5
              local.get 1
              i32.add
              local.tee 6
              i32.const -1
              i32.le_s
              br_if 2 (;@3;)
              i32.const 2147483647
              local.set 7
              block  ;; label = @6
                local.get 2
                local.get 4
                i32.sub
                local.tee 2
                i32.const 1073741822
                i32.gt_u
                br_if 0 (;@6;)
                local.get 6
                local.get 2
                i32.const 1
                i32.shl
                local.tee 2
                local.get 2
                local.get 6
                i32.lt_u
                select
                local.tee 7
                i32.eqz
                br_if 2 (;@4;)
              end
              local.get 7
              call 45
              local.set 2
              br 3 (;@2;)
            end
            local.get 0
            i32.const 4
            i32.add
            local.set 0
            loop  ;; label = @5
              local.get 3
              i32.const 0
              i32.store8
              local.get 0
              local.get 0
              i32.load
              i32.const 1
              i32.add
              local.tee 3
              i32.store
              local.get 1
              i32.const -1
              i32.add
              local.tee 1
              br_if 0 (;@5;)
              br 4 (;@1;)
            end
          end
          i32.const 0
          local.set 7
          i32.const 0
          local.set 2
          br 1 (;@2;)
        end
        local.get 0
        call 56
        unreachable
      end
      local.get 2
      local.get 7
      i32.add
      local.set 7
      local.get 3
      local.get 1
      i32.add
      local.get 4
      i32.sub
      local.set 4
      local.get 2
      local.get 5
      i32.add
      local.tee 5
      local.set 3
      loop  ;; label = @2
        local.get 3
        i32.const 0
        i32.store8
        local.get 3
        i32.const 1
        i32.add
        local.set 3
        local.get 1
        i32.const -1
        i32.add
        local.tee 1
        br_if 0 (;@2;)
      end
      local.get 2
      local.get 4
      i32.add
      local.set 4
      local.get 5
      local.get 0
      i32.const 4
      i32.add
      local.tee 6
      i32.load
      local.get 0
      i32.load
      local.tee 1
      i32.sub
      local.tee 3
      i32.sub
      local.set 2
      block  ;; label = @2
        local.get 3
        i32.const 1
        i32.lt_s
        br_if 0 (;@2;)
        local.get 2
        local.get 1
        local.get 3
        call 8
        drop
        local.get 0
        i32.load
        local.set 1
      end
      local.get 0
      local.get 2
      i32.store
      local.get 6
      local.get 4
      i32.store
      local.get 0
      i32.const 8
      i32.add
      local.get 7
      i32.store
      local.get 1
      i32.eqz
      br_if 0 (;@1;)
      local.get 1
      call 47
      return
    end)
  (table (;0;) 1 1 funcref)
  (memory (;0;) 1)
  (global (;0;) (mut i32) (i32.const 8192))
  (global (;1;) i32 (i32.const 9638))
  (global (;2;) i32 (i32.const 9638))
  (export "apply" (func 38))
  (data (;0;) (i32.const 8220) "failed to allocate pages\00invalid symbol name\00")
  (data (;1;) (i32.const 8265) "invalid supply\00")
  (data (;2;) (i32.const 8280) "max-supply must be positive\00")
  (data (;3;) (i32.const 8308) "token with symbol already exists\00")
  (data (;4;) (i32.const 8341) "memo has more than 256 bytes\00")
  (data (;5;) (i32.const 8370) "token with symbol does not exist, create token before issue\00")
  (data (;6;) (i32.const 8430) "tokens can only be issued to issuer account\00")
  (data (;7;) (i32.const 8474) "invalid quantity\00")
  (data (;8;) (i32.const 8491) "must issue positive quantity\00")
  (data (;9;) (i32.const 8520) "symbol precision mismatch\00")
  (data (;10;) (i32.const 8546) "quantity exceeds available supply\00")
  (data (;11;) (i32.const 8580) "token with symbol does not exist\00")
  (data (;12;) (i32.const 8613) "must retire positive quantity\00")
  (data (;13;) (i32.const 8643) "cannot transfer to self\00")
  (data (;14;) (i32.const 8667) "to account does not exist\00")
  (data (;15;) (i32.const 8693) "unable to find key\00")
  (data (;16;) (i32.const 8712) "must transfer positive quantity\00")
  (data (;17;) (i32.const 8744) "no balance object found\00")
  (data (;18;) (i32.const 8768) "overdrawn balance\00")
  (data (;19;) (i32.const 8786) "owner account does not exist\00")
  (data (;20;) (i32.const 8815) "symbol does not exist\00")
  (data (;21;) (i32.const 8837) "Balance row already deleted or never existed. Action won't have any effect.\00")
  (data (;22;) (i32.const 8913) "Cannot close because the balance is not zero.\00")
  (data (;23;) (i32.const 8959) "object passed to iterator_to is not in multi_index\00")
  (data (;24;) (i32.const 9010) "error reading iterator\00")
  (data (;25;) (i32.const 9033) "cannot create objects in table of another contract\00")
  (data (;26;) (i32.const 9084) "write\00")
  (data (;27;) (i32.const 9090) "object passed to modify is not in multi_index\00")
  (data (;28;) (i32.const 9136) "cannot modify objects in table of another contract\00")
  (data (;29;) (i32.const 9187) "updater cannot change primary key when modifying an object\00")
  (data (;30;) (i32.const 9246) "attempt to add asset with different symbol\00")
  (data (;31;) (i32.const 9289) "addition underflow\00")
  (data (;32;) (i32.const 9308) "addition overflow\00")
  (data (;33;) (i32.const 9326) "attempt to subtract asset with different symbol\00")
  (data (;34;) (i32.const 9374) "subtraction underflow\00")
  (data (;35;) (i32.const 9396) "subtraction overflow\00")
  (data (;36;) (i32.const 9417) "cannot pass end iterator to erase\00")
  (data (;37;) (i32.const 9451) "cannot increment end iterator\00")
  (data (;38;) (i32.const 9481) "object passed to erase is not in multi_index\00")
  (data (;39;) (i32.const 9526) "cannot erase objects in table of another contract\00")
  (data (;40;) (i32.const 9576) "attempt to remove object that was not in multi_index\00")
  (data (;41;) (i32.const 9629) "read\00")
  (data (;42;) (i32.const 9634) "get\00")
  (data (;43;) (i32.const 0) "\a8%\00\00"))
