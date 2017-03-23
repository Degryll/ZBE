tempalte <typename T>
class CollisionerCommonAdaptor : Adaptor<Collisioner> {
public:
  CollisionerCommonAdaptor(const DummyAdaptorC&) = delete;
  void operator=(const CollisionerCommonAdaptor&) = delete;

  CollisionerCommonAdaptor(AvatatEntity<T>* aet,
          std::shared_ptr<CollisionObject<R> > collisionObject,
          std::shared_ptr<ReactObject<R> > reactObject,
          uint64_t actuatorsList) :
              aet(aet),
              cct(nullptr),
              co(collisionObject),
              ro(reactObject),
              al(actuatorsList))  {}
  Collisioner* getAvatar() {
      delete cct;
      T* t;
      aet->assingAvatar(&t);
      cct = new CollisionerCommon(t, asdasdasd);
      return (cct);
  }
private:
  AvatatEntity<T>* aet;
  CollisionerCommon<T>* cct;
    std::shared_ptr<CollisionObject<R> > co;  //!< Collision object
    std::shared_ptr<ReactObject<R> > ro;  //!< Collision object
    uint64_t al;
};
